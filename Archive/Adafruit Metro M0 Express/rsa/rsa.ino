/***************
  STILL IN PRIGRESS
  Comments are left in places where it needs work one.
  Those comments will be removed once relevant information is filled.
 ***************/

/** need to choose which RSA implementation to run **/
//#define tiny_rsa
//#define codebase
//#define navin
#define bearssl_rsa

/** the two implementations are what me and William are struggling with **/
//#define mbedtls_rsa

/** need to uncomment the board you are using **/
//#define msp432p401r
//#define riscv
#define adafruitm0express
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// DO NOT EDIT BELOW  //////////////////////////////////////////
#ifdef msp432p401r
#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#endif

#ifdef msp430g2553
#include "msp430.h"
#endif

#ifdef msp430fr5994
#include "msp430.h"
#endif

#include "experiment_time.h"

#ifdef tiny_rsa
#include "tiny_rsa/rsa_test.h"
#endif
#ifdef codebase
#include "codebase/rsa.h"
#include "codebase/rsa.c"
#endif
#ifdef navin
#include "navin/rsa.h"
#include "navin/rsa.c"
#endif
#ifdef bearssl_rsa
#include "bearssl/bearssl_rsa.h"
#include "bearssl/bearssl.h"
#include "bearssl/inner.h"
#include "bearssl/rsa_i15_oaep_encrypt.c"
#include "bearssl/rsa_i15_oaep_decrypt.c"
#include "bearssl/rsa_oaep_pad.c"
#include "bearssl/rsa_oaep_unpad.c"
#include "bearssl/mgf1.c"
#include "bearssl/rsa_i15_pub.c"
#include "bearssl/rsa_i15_priv.c"
#include "bearssl/i15_decode.c"
#include "bearssl/i15_bitlen.c"
#include "bearssl/i15_ninv15.c"
#include "bearssl/i15_decmod.c"
#include "bearssl/i15_modpow2.c"
#include "bearssl/i15_tmont.c"
#include "bearssl/i15_muladd.c"
#include "bearssl/i15_mulacc.c"
#include "bearssl/i15_encode.c"
#include "bearssl/i15_add.c"
#include "bearssl/i15_sub.c"
#include "bearssl/i15_fmont.c"
#include "bearssl/i15_montmul.c"
#include "bearssl/ccopy.c"
#include "bearssl/sha1.c"
#include "bearssl/enc32be.c"
#include "bearssl/dec32be.c"
#include "bearssl/i15_reduce.c"
#include "bearssl/i15_decred.c"
#include "bearssl/i15_rshift.c"
#endif
#ifdef  mbedtls_rsa
#include "mbedtls/pk.h"
#endif

/** Globals (test inputs) **/
//define the global variables here
#ifdef mbedtls_rsa

char resultBuffer[8192];
char public[] =
        "a15f36fc7f8d188057fc51751962a5977118fa2ad4ced249c039ce36c8d1bd275273f1edd821892fa75680b1ae38749fff9268bf06b3c2af02bbdb52a0d05c2ae2384aa1002391c4b16b87caea8296cfd43757bb51373412e8fe5df2e56370505b692cf8d966e3f16bc62629874a0464a9710e4a0718637a68442e0eb1648ec5";
char private[] =
        "3f5cc8956a6bf773e598604faf71097e265d5d55560c038c0bdb66ba222e20ac80f69fc6f93769cb795440e2037b8d67898d6e6d9b6f180169fc6348d5761ac9e81f6b8879529bc07c28dc92609eb8a4d15ac4ba3168a331403c689b1e82f62518c38601d58fd628fcb7009f139fb98e61ef7a23bee4e3d50af709638c24133d";
char cipher[] =
        "1cb1c5e45e584cb1b627cac7b0de0812dac7c1d1638785a7660f6772d219f62aa0ce3e8a853abadebe0a293d76a17d321da8b1fd25ddf807ce96006f73a0aed014b990d6025c42b6c216d8553b66e724270b6dbd654d55e368edeacbc8da30f0cbe5ccbb72a3fe44d29543a5bbb5255a404234ce53bf70f52a78170685a6e391";
int plaintext = 54321;

#endif
#ifdef tiny_rsa

char resultBuffer[8192];
char public[] =
        "a15f36fc7f8d188057fc51751962a5977118fa2ad4ced249c039ce36c8d1bd275273f1edd821892fa75680b1ae38749fff9268bf06b3c2af02bbdb52a0d05c2ae2384aa1002391c4b16b87caea8296cfd43757bb51373412e8fe5df2e56370505b692cf8d966e3f16bc62629874a0464a9710e4a0718637a68442e0eb1648ec5";
char private[] =
        "3f5cc8956a6bf773e598604faf71097e265d5d55560c038c0bdb66ba222e20ac80f69fc6f93769cb795440e2037b8d67898d6e6d9b6f180169fc6348d5761ac9e81f6b8879529bc07c28dc92609eb8a4d15ac4ba3168a331403c689b1e82f62518c38601d58fd628fcb7009f139fb98e61ef7a23bee4e3d50af709638c24133d";
char cipher[] =
        "1cb1c5e45e584cb1b627cac7b0de0812dac7c1d1638785a7660f6772d219f62aa0ce3e8a853abadebe0a293d76a17d321da8b1fd25ddf807ce96006f73a0aed014b990d6025c42b6c216d8553b66e724270b6dbd654d55e368edeacbc8da30f0cbe5ccbb72a3fe44d29543a5bbb5255a404234ce53bf70f52a78170685a6e391";
int plaintext = 54321;

#endif
#ifdef codebase

uint64_t plaintext = 54321;
uint64_t cipher = 351159;
uint64_t rsaDecrypted, rsaEncrypted;

#endif
#ifdef navin

uint64_t resultBuffer[1024];
char public[] =
        "a15f36fc7f8d188057fc51751962a5977118fa2ad4ced249c039ce36c8d1bd275273f1edd821892fa75680b1ae38749fff9268bf06b3c2af02bbdb52a0d05c2ae2384aa1002391c4b16b87caea8296cfd43757bb51373412e8fe5df2e56370505b692cf8d966e3f16bc62629874a0464a9710e4a0718637a68442e0eb1648ec5";
char private[] =
        "3f5cc8956a6bf773e598604faf71097e265d5d55560c038c0bdb66ba222e20ac80f69fc6f93769cb795440e2037b8d67898d6e6d9b6f180169fc6348d5761ac9e81f6b8879529bc07c28dc92609eb8a4d15ac4ba3168a331403c689b1e82f62518c38601d58fd628fcb7009f139fb98e61ef7a23bee4e3d50af709638c24133d";
char cipher[] =
        "1cb1c5e45e584cb1b627cac7b0de0812dac7c1d1638785a7660f6772d219f62aa0ce3e8a853abadebe0a293d76a17d321da8b1fd25ddf807ce96006f73a0aed014b990d6025c42b6c216d8553b66e724270b6dbd654d55e368edeacbc8da30f0cbe5ccbb72a3fe44d29543a5bbb5255a404234ce53bf70f52a78170685a6e391";
uint8_t plaintext[] = {5, 4, 3, 2, 1};

#endif
#ifdef bearssl_rsa

/*
 * Test vectors from pkcs-1v2-1d2-vec.zip (originally from ftp.rsa.com).
 * There are ten RSA keys, and for each RSA key, there are 6 messages,
 * each with an explicit seed.
 */
static const char *KAT_RSA_OAEP[] =
{
 /* 1024-bit key, from oeap-int.txt */
 //public key
 "BBF82F090682CE9C2338AC2B9DA871F7368D07EED41043A440D6B6F07454F51FB8DFBAAF035C02AB61EA48CEEB6FCD4876ED520D60E1EC4619719D8A5B8B807FAFB8E0A3DFC737723EE6B4B7D93A2584EE6A649D060953748834B2454598394EE0AAB12D7B61A51F527A9A41F6C1687FE2537298CA2A8F5946F8E5FD091DBDCB",
 "11",
 //private
 "EECFAE81B1B9B3C908810B10A1B5600199EB9F44AEF4FDA493B81A9E3D84F632124EF0236E5D1E3B7E28FAE7AA040A2D5B252176459D1F397541BA2A58FB6599",
 "C97FB1F027F453F6341233EAAAD1D9353F6C42D08866B1D05A0F2035028B9D869840B41666B42E92EA0DA3B43204B5CFCE3352524D0416A5A441E700AF461503",
 "54494CA63EBA0337E4E24023FCD69A5AEB07DDDC0183A4D0AC9B54B051F2B13ED9490975EAB77414FF59C1F7692E9A2E202B38FC910A474174ADC93C1F67C981",
 "471E0290FF0AF0750351B7F878864CA961ADBD3A8A7E991C5C0556A94C3146A7F9803F8F6F8AE342E931FD8AE47A220D1B99A495849807FE39F9245A9836DA3D",
 "B06C4FDABB6301198D265BDBAE9423B380F271F73453885093077FCD39E2119FC98632154F5883B167A967BF402B4E9E2E0F9656E698EA3666EDFB25798039F7",

 /* oaep-int.txt contains only one message, so we repeat it six
           times to respect our array format. */

 //plain text
 "D436E99569FD32A7C8A05BBC90D32C49",
 // seed
 "AAFD12F659CAE63489B479E5076DDEC2F06CB58F",
 //cipher text
 "1253E04DC0A5397BB44A7AB87E9BF2A039A33D1E996FC82A94CCD30074C95DF763722017069E5268DA5D1C0B4F872CF653C11DF82314A67968DFEAE28DEF04BB6D84B1C31D654A1970E5783BD6EB96A024C2CA2F4A90FE9F2EF5C9C140E5BB48DA9536AD8700C84FC9130ADEA74E558D51A74DDF85D8B50DE96838D6063E0955",

 NULL };

unsigned char resultBuffer[1024];
unsigned char plain[512], seed[128], cipher[512];
size_t check_result_len;

#endif

/** Initialization for different RSA implementations **/

#ifdef tiny_rsa
// Nothing needs to be done.
#endif
#ifdef codebase

// Values based on 64-bit math (huge_t = uint64_t)
// which will result in more secure encryption, but also
// increases the size of the encrypted text

rsaPubKey_t publicKey = {21, 16484947};
rsaPriKey_t privateKey = {15689981, 16484947};

//publicKey.e = 21;
//publicKey.n = 16484947;
//privateKey.d = 15689981;
//privateKey.n = 16484947;

#endif
#ifdef navin
// Nothing needs to be done.
#endif
#ifdef bearssl_rsa

static size_t hextobin(unsigned char *dst, const char *src)
{
    size_t num;
    unsigned acc;
    int z;

    num = 0;
    z = 0;
    acc = 0;
    while (*src != 0)
    {
        int c = *src++;
        if (c >= '0' && c <= '9')
        {
            c -= '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            c -= ('A' - 10);
        }
        else if (c >= 'a' && c <= 'f')
        {
            c -= ('a' - 10);
        }
        else
        {
            continue;
        }
        if (z)
        {
            *dst++ = (acc << 4) + c;
            num++;
        }
        else
        {
            acc = c;
        }
        z = !z;
    }
    return num;
}

// Fake RNG that returns exactly the provided bytes.
typedef struct
{
    const br_prng_class *vtable;
    unsigned char buf[128];
    size_t ptr, len;
} rng_fake_ctx;

static void rng_fake_init(rng_fake_ctx *cc, const void *params,
                          const void *seed, size_t len);
static void rng_fake_generate(rng_fake_ctx *cc, void *dst, size_t len);
static void rng_fake_update(rng_fake_ctx *cc, const void *src, size_t len);

static const br_prng_class rng_fake_vtable =
{ sizeof(rng_fake_ctx),
  (void (*)(const br_prng_class**, const void*, const void*, size_t)) &rng_fake_init,
  (void (*)(const br_prng_class**, void*, size_t)) &rng_fake_generate,
  (void (*)(const br_prng_class**, const void*, size_t)) &rng_fake_update };

static void rng_fake_init(rng_fake_ctx *cc, const void *params,
                          const void *seed, size_t len)
{
    (void) params;
    if (len > sizeof cc->buf)
    {
        fprintf(stderr, "seed is too large (%lu bytes)\n", (unsigned long) len);
        exit(EXIT_FAILURE);
    }
    cc->vtable = &rng_fake_vtable;
    memcpy(cc->buf, seed, len);
    cc->ptr = 0;
    cc->len = len;
}

static void rng_fake_generate(rng_fake_ctx *cc, void *dst, size_t len)
{
    if (len > (cc->len - cc->ptr))
    {
        fprintf(stderr, "asking for more data than expected\n");
        exit(EXIT_FAILURE);
    }
    memcpy(dst, cc->buf + cc->ptr, len);
    cc->ptr += len;
}

static void rng_fake_update(rng_fake_ctx *cc, const void *src, size_t len)
{
    (void) cc;
    (void) src;
    (void) len;
    fprintf(stderr, "unexpected update\n");
    exit(EXIT_FAILURE);
}

#endif

void test_encrypt()
{
#ifdef tiny_rsa
    rsa1024_encrypt(public, private, resultBuffer, plaintext);
#endif
#ifdef codebase
    rsaEncrypt(plaintext, &rsaEncrypted, publicKey);
#endif
#ifdef navin
    uint64_t e[18] = {0};
    e[0] = 65537;

    rsa1024(resultBuffer, plaintext, public, e);
#endif
#ifdef bearssl_rsa

    size_t u;
    u = 0;

    unsigned char n[512];
    unsigned char e[8];
    unsigned char p[256];
    unsigned char q[256];
    unsigned char dp[256];
    unsigned char dq[256];
    unsigned char iq[256];
    br_rsa_public_key pk;
    br_rsa_private_key sk;
    size_t v;

    pk.n = n;
    pk.nlen = hextobin(n, KAT_RSA_OAEP[u++]);
    pk.e = e;
    pk.elen = hextobin(e, KAT_RSA_OAEP[u++]);

    for (v = 0; n[v] == 0; v++)
        ;
    sk.n_bitlen = BIT_LENGTH(n[v]) + ((pk.nlen - 1 - v) << 3);
    sk.p = p;
    sk.plen = hextobin(p, KAT_RSA_OAEP[u++]);
    sk.q = q;
    sk.qlen = hextobin(q, KAT_RSA_OAEP[u++]);
    sk.dp = dp;
    sk.dplen = hextobin(dp, KAT_RSA_OAEP[u++]);
    sk.dq = dq;
    sk.dqlen = hextobin(dq, KAT_RSA_OAEP[u++]);
    sk.iq = iq;
    sk.iqlen = hextobin(iq, KAT_RSA_OAEP[u++]);

    size_t plain_len, seed_len, cipher_len;
    rng_fake_ctx rng;

    plain_len = hextobin(plain, KAT_RSA_OAEP[u++]);
    seed_len = hextobin(seed, KAT_RSA_OAEP[u++]);
    cipher_len = hextobin(cipher, KAT_RSA_OAEP[u++]);
    rng_fake_init(&rng, NULL, seed, seed_len);

    br_rsa_i15_oaep_encrypt(&rng.vtable, &br_sha1_vtable, NULL, 0, &pk, resultBuffer, sizeof resultBuffer, plain, plain_len);

#endif
#ifdef mbedtls_rsa
    size_t olen = 0;

    mbedtls_pk_context pk;
    mbedtls_pk_init( &pk );
    mbedtls_pk_parse_public_keyfile( &pk, "our-key.pub" );

    mbedtls_pk_encrypt( &pk, plaintext, sizeof(plaintext),
                        resultBuffer, &olen, sizeof(resultBuffer),
                        NULL, NULL );
#endif
}

void test_decrypt()
{
#ifdef tiny_rsa
    rsa1024_decrypt(public, private, resultBuffer, cipher);
#endif
#ifdef codebase
    rsaDecrypt(cipher, &rsaDecrypted, privateKey);
#endif
#ifdef navin
    uint64_t e[18] = {0};
    e[0] = 65537;

    rsa1024(resultBuffer, ciphertext, private, e);
#endif
#ifdef bearssl_rsa

    size_t u;
    u = 0;

    unsigned char n[512];
    unsigned char e[8];
    unsigned char p[256];
    unsigned char q[256];
    unsigned char dp[256];
    unsigned char dq[256];
    unsigned char iq[256];
    br_rsa_public_key pk;
    br_rsa_private_key sk;
    size_t v;

    pk.n = n;
    pk.nlen = hextobin(n, KAT_RSA_OAEP[u++]);
    pk.e = e;
    pk.elen = hextobin(e, KAT_RSA_OAEP[u++]);

    for (v = 0; n[v] == 0; v++)
        ;
    sk.n_bitlen = BIT_LENGTH(n[v]) + ((pk.nlen - 1 - v) << 3);
    sk.p = p;
    sk.plen = hextobin(p, KAT_RSA_OAEP[u++]);
    sk.q = q;
    sk.qlen = hextobin(q, KAT_RSA_OAEP[u++]);
    sk.dp = dp;
    sk.dplen = hextobin(dp, KAT_RSA_OAEP[u++]);
    sk.dq = dq;
    sk.dqlen = hextobin(dq, KAT_RSA_OAEP[u++]);
    sk.iq = iq;
    sk.iqlen = hextobin(iq, KAT_RSA_OAEP[u++]);

    size_t plain_len, seed_len, cipher_len;
    rng_fake_ctx rng;

    plain_len = hextobin(plain, KAT_RSA_OAEP[u++]);
    seed_len = hextobin(seed, KAT_RSA_OAEP[u++]);
    cipher_len = hextobin(cipher, KAT_RSA_OAEP[u++]);
    rng_fake_init(&rng, NULL, seed, seed_len);

    for(int i = 0; i < sizeof(plain); i++) {
        resultBuffer[i] = plain[i];
    }

    br_rsa_i15_oaep_decrypt(&br_sha1_vtable, NULL, 0, &sk, resultBuffer, (size_t*) sizeof resultBuffer);
#endif
#ifdef mbedtls_rsa
    size_t olen = 0;

    mbedtls_pk_context pk;
    mbedtls_pk_init( &pk );
    mbedtls_pk_parse_public_keyfile( &pk, "our-key.prv" );

    mbedtls_pk_decrypt( &pk, plaintext, sizeof(plaintext),
                        resultBuffer, &olen, sizeof(resultBuffer),
                        NULL, NULL );
#endif
}

//int check_encrypt()
//{
//#if defined(tiny_rsa)
//    return memcmp((char*) cipher, (char*) resultBuffer, sizeof(cipher));
//#elif defined(bearssl_rsa)
//    return memcmp((char*) cipher, (char*) resultBuffer, sizeof(cipher));
//#elif defined(codebase)
//    return (cipher == rsaEncrypted);
//#elif defined(navin)
//    return memcmp((char*) cipher, (char*) resultBuffer, sizeof(cipher));
//#endif
//}
//
//int check_decrypt()
//{
//#if defined(tiny_rsa)
//    return memcmp((char*) plaintext, (char*) resultBuffer, sizeof(plaintext));
//#elif defined(bearssl_rsa)
//    return memcmp((char*) plain, (char*) resultBuffer, sizeof(plain));
//#elif defined(codebase)
//    return (plaintext == rsaDecrypted);
//#elif defined(navin)
//    return memcmp((char*) plaintext, (char*) resultBuffer, sizeof(plaintext));
//#endif
//}

void setup() {
  Serial.begin(9600);
}

void loop() {

#ifdef msp432p401r
  /** Initialize the board **/
  board_init();

  /** Starting the timer to measure elapsed time **/
  startTimer();
#endif
#ifdef adafruitm0express
  /** Measure the starting time **/
  setup();
  unsigned long start, finished, elapsed;
  start = micros();
#endif

  /** initialize navin RSA **/
//  init_navin();
  
  /** test rsa **/
  test_encrypt();
//  test_decrypt();

  /** Check the result to see whether RSA algorithm is correctly working or not **/
//  check_result();

#ifdef msp432p401r
  volatile unsigned int elapsed = getElapsedTime();
#endif
#ifdef adafruitm0express
  /** Calculate the elapsed time **/
  finished = micros();
  elapsed = finished - start;
  Serial.print("Time taken by the task: ");
  Serial.println(elapsed);

  // wait a second so as not to send massive amounts of data
  delay(1000);
#endif

  // while (1);
}
