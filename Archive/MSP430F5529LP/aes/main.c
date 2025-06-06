#include "test.h" // Change test.h to select different algorithms

#include <stdint.h>
#include <string.h>

#ifdef msp432p401r
#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#endif

#if defined msp430g2553 || defined msp430f5529 || defined msp430fr5994
#include "msp430.h"
#endif

#include "experiment_time.h"

#ifdef gladman_aes
#include "gladman/aestst.h"
#endif

#ifdef tiny_aes
#include "tiny_aes/aes.h"
#endif

#ifdef slow_tiny_aes
#include "slow_tiny_aes/aes.h"
#endif

#ifdef mbedtls_aes
#include "mbedtls/aes.h"
#endif

/** Globals (test inputs) **/
uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73,
                  0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07,
                  0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14,
                  0xdf, 0xf4 };
uint8_t expected_pt[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                            0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
uint8_t expected_ct[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c,
                            0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };

#ifdef AES_CBC
uint8_t pt[MSG_LNGTH];
uint8_t ct[MSG_LNGTH];
// initialization vector for CBC mode
unsigned char iv[AES_BLOCK_SIZE_BYTES] = { 0xb2, 0x4b, 0xf2, 0xf7, 0x7a, 0xc5, 0xec, 0x0c, 0x5e,
                         0x1f, 0x4d, 0xc1, 0xae, 0x46, 0x5e, 0x75 };
#else
uint8_t pt[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d,
                 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
uint8_t ct[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b,
                 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#endif

/** contexts **/
#ifdef tiny_aes
struct AES_ctx ctx;
#endif
#ifdef mbedtls_aes
struct mbedtls_aes_context ctx;
#endif

/** define keysizes **/
#if defined AES_128
long keysize = 128;
#elif defined AES_192
long keysize = 192;
#else
long keysize = 256;
#endif

/** Call initialization functions for different AES implementations **/
void init_aes()
{
#ifdef gladman_aes
    gladman_init(key, pt, ct, keysize);
#endif
#ifdef tiny_aes
    AES_init_ctx(&ctx, key);
#endif
#ifdef mbedtls_aes
    mbedtls_aes_init(&ctx);
#endif
}

void test_encrypt()
{
    /** Gladman AES **/
#ifdef gladman_aes
#ifdef AES_128
    aes_gladman_128_encrypt(key, pt, ct);
#elif AES_192
    aes_gladman_192_encrypt(key, pt, ct);
#else // AES_256
    aes_gladman_256_encrypt(key, pt, ct);
#endif
#endif

    /** tiny AES **/
#ifdef tiny_aes
    AES_encrypt(&ctx, key, pt, ct);
#endif

    /** SLOW tiny AES **/
#ifdef slow_tiny_aes
    test_AES_encrypt();
#endif

    /** MbedTLS AES **/
#ifdef mbedtls_aes
    mbedtls_aes_setkey_enc(&ctx, key, keysize);
    mbedtls_internal_aes_encrypt(&ctx, pt, ct);
#endif
}

void test_decrypt()
{
    /** Gladman AES **/
#ifdef gladman_aes
#ifdef AES_128
    aes_gladman_128_decrypt(key, ct, pt);
#elif AES_192
    aes_gladman_192_decrypt(key, ct, pt);
#else // AES_256
    aes_gladman_256_decrypt(key, ct, pt);
#endif
#endif

    /** tiny AES **/
#ifdef tiny_aes
    AES_decrypt(&ctx, key, ct, pt);
#endif

    /** SLOW tiny AES **/
#ifdef slow_tiny_aes
    test_AES_decrypt();
#endif

    /** MbedTLS AES **/
#ifdef mbedtls_aes
    mbedtls_aes_setkey_dec(&ctx, key, keysize);
    mbedtls_internal_aes_decrypt(&ctx, ct, pt);
#endif
}

///******************************
// *
// * Function to verify encryption
// *
// ******************************/
//int check_encrypt() {
//    return memcmp((char*) expected_ct, (char*) ct, sizeof(expected_ct));
//}
//
///******************************
// *
// * Function to verify decryption
// *
// ******************************/
//int check_decrypt() {
//    return memcmp((char*) expected_pt, (char*) pt, sizeof(expected_pt));
//}

#ifdef AES_CBC
void aes_encrypt_cbc(size_t length) {
    uint8_t * p = pt;
    uint8_t * c = ct;

    while (length > 0) {
        // Perform IV xor PT for 128 bits
        int i = 0;
        for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
            p[i] = p[i] ^ iv[i];

        // Perform 1 encrypt
        test_encrypt();

        // IV is now CT
        memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

        // Go to next block of PT
        p += AES_BLOCK_SIZE_BYTES;
        c += AES_BLOCK_SIZE_BYTES;
        length -= AES_BLOCK_SIZE_BYTES;
    }
}

void aes_decrypt_cbc(size_t length) {
    uint8_t * p = pt;
    uint8_t * c = ct;

    while (length > 0) {
        // Perform 1 encrypt
        test_decrypt();

        // Perform IV xor PT for 128 bits
        int i = 0;
        for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
             p[i] = p[i] ^ iv[i];

        // IV is now CT
        memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

        // Go to next block of PT
        p += AES_BLOCK_SIZE_BYTES;
        c += AES_BLOCK_SIZE_BYTES;
        length -= AES_BLOCK_SIZE_BYTES;
    }
}
#endif

void main(void) {
    board_init();

    startTimer();

    /** initialize AES **/
    init_aes();

    /** Choose the function to be called **/
    /** Encrypt or decrypt possibly many times **/
//    test_encrypt();
    test_decrypt();
//    aes_encrypt_cbc(sizeof(pt));
    //aes_decrypt_cbc(sizeof(ct));

    /** Check the result to see whether AES algorithm is correctly working or not **/
//    volatile unsigned int verify = check_encrypt(); // Check the validity of an encryption method
//    volatile unsigned int verify = check_decrypt(); // Check the validity of a decryption method

    volatile unsigned int elapsed = getElapsedTime();

    while (1);
}
