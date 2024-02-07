#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cmac.h"
#include "../../aes/aes.h"
#include "utils.h"
#include "../config.h"

#ifdef gladman_cmac
#include "../../aes/gladman/aestst.h"
#endif

#ifdef tiny_cmac
#include "../../aes/tiny_aes/aes.h"
#endif

#ifdef mbedtls_cmac
#include "../../aes/mbedtls/aes.h"
#endif

/** contexts **/
#ifdef tiny_cmac
struct AES_ctx ctx;
#endif
#ifdef mbedtls_cmac
struct mbedtls_aes_context ctx;
#endif

long keysize = 128;

void init_aes_context(unsigned char* key){
#ifdef tiny_cmac
    AES_init_ctx(&ctx, key);
#endif
#ifdef mbedtls_cmac
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, key, keysize);
#endif
}

// Calculate the CMAC
unsigned char* aes_cmac(unsigned char* in, unsigned int length, unsigned char* out, unsigned char* key)
{
    unsigned char* K1;
    unsigned char* K2;
    unsigned char* ct[16];
    K1 = (unsigned char*)malloc(16);
    K2 = (unsigned char*)malloc(16);
    GenerateSubkey(key, K1, K2);

    int n = (length / const_Bsize);
    bool flag = false;
    if (length % const_Bsize != 0) {
        n++;
    }

    if (n == 0) {
        n = 1;
    } else if (length % const_Bsize == 0) {
        flag = true;
    }

    unsigned char M[n][const_Bsize];
    memset(M[0], 0, n * const_Bsize);
    memcpy(M[0], in, length);
    if (!flag) {
        memset(M[0] + length, 0x80, 1);
    }
    if (flag) {
        block_xor_cmac(M[n - 1], M[n - 1], K1);
    } else {
        block_xor_cmac(M[n - 1], M[n - 1], K2);
    }

    unsigned char X[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    unsigned char Y[const_Bsize];


    init_aes_context(key);
    auto i = 0;
    for (i = 0; i < n - 1; i++) {
        block_xor_cmac(Y, M[i], X);
//        aes_128_encrypt(Y, X, key);
#ifdef gladman_cmac
        aes_gladman_128_encrypt(key, Y, ct, X);
#endif
#ifdef tiny_cmac
        memcpy(X, Y, 16);
        AES_encrypt(&ctx, key, X, X);
#endif
#ifdef mbedtls_cmac
        mbedtls_internal_aes_encrypt(&ctx, Y, X);
#endif

    }
    block_xor_cmac(Y, M[n - 1], X);
//    aes_128_encrypt(Y, out, key);
#ifdef gladman_cmac
    aes_gladman_128_encrypt(key, Y, ct, out);
#endif
#ifdef tiny_cmac
    memcpy(out, Y, 16);
    AES_encrypt(&ctx, key, out, out);
#endif
#ifdef mbedtls_cmac
    mbedtls_internal_aes_encrypt(&ctx, Y, out);
#endif
    free(K1);
    free(K2);
    return out;
}

// Verify the CMAC
bool verify_mac(unsigned char* in, unsigned int length, unsigned char* out, unsigned char* key)
{
    bool flag = true;
    unsigned char result[16];
    aes_cmac(in, length, (unsigned char*)result, key);
    auto i = 0;
    for (i = 0; i < const_Bsize; i++) {
        if (!(result[i] ^ out[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

// Generate the Sub keys
void GenerateSubkey(unsigned char* key, unsigned char* K1, unsigned char* K2)
{
    unsigned char const_Zero[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    unsigned char const_Rb[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x87
    };

    unsigned char L[16];
    aes_128_encrypt(const_Zero, L, key);
    block_leftshift(K1, L);
    if (L[0] & 0x80) {
        block_xor_cmac(K1, K1, const_Rb);
    }

    block_leftshift(K2, K1);
    if (K1[0] & 0x80) {
        block_xor_cmac(K2, K2, const_Rb);
    }
}
