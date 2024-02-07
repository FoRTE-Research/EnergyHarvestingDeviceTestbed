/*
   hmac_sha256.c
   Originally written by https://github.com/h5p9sl
 */

/** need to choose which SHA implementation to run **/

#include "hmac_sha256.h"

#include <stdlib.h>
#include <string.h>
#include "../config.h"

#ifdef gladman_sha
#include "../../sha/gladman/sha2.h"
#endif
#ifdef saddi_sha
#include "../../sha/saddi/sha256.h"
#endif
#ifdef mbedtls_sha
#include "../../sha/mbedtls/sha256.h"
#endif


#define SHA256_BLOCK_SIZE 64
#define SHA256_HASH_SIZE (256/8)

/** contexts **/
#ifdef gladman_sha
    sha256_ctx cx[1];
#endif
#ifdef saddi_sha
    SHA256_CTX ctx;
#endif
#ifdef mbedtls_sha
    mbedtls_sha256_context ctx;
#endif

/* LOCAL FUNCTIONS */
void init_sha_context()
{
#ifdef gladman_sha
    sha256_begin(cx);
#endif
#ifdef saddi_sha
    sha256_init (&ctx);
#endif
#ifdef mbedtls_aes
    mbedtls_sha256_init(&ctx);
#endif
}

// Concatenate X & Y, return hash.
static void* H(const void* x,
               const size_t xlen,
               const void* y,
               const size_t ylen,
               void* out,
               const size_t outlen);

// Declared in hmac_sha256.h
size_t hmac_sha256(const void* key,
                   const size_t keylen,
                   const void* data,
                   const size_t datalen,
                   void* out,
                   const size_t outlen) {
  uint8_t k[SHA256_BLOCK_SIZE];
  uint8_t k_ipad[SHA256_BLOCK_SIZE];
  uint8_t k_opad[SHA256_BLOCK_SIZE];
  uint8_t ihash[SHA256_HASH_SIZE];
  uint8_t ohash[SHA256_HASH_SIZE];
  size_t sz;
  int i;

  memset(k, 0, sizeof(k));
  memset(k_ipad, 0x36, SHA256_BLOCK_SIZE);
  memset(k_opad, 0x5c, SHA256_BLOCK_SIZE);

  // if we need longer key length
//  if (keylen > SHA256_BLOCK_SIZE) {
//    // If the key is larger than the hash algorithm's
//    // block size, we must digest it first.
//    init_sha_context();
//    sha(k, key, keylen, cx);
//  }
//  else {
//    memcpy(k, key, keylen);
//  }

  memcpy(k, key, keylen);

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    k_ipad[i] ^= k[i];
    k_opad[i] ^= k[i];
  }

  // Perform HMAC algorithm: ( https://tools.ietf.org/html/rfc2104 )
  //      `H(K XOR opad, H(K XOR ipad, data))`
  H(k_ipad, sizeof(k_ipad), data, datalen, ihash, sizeof(ihash));
  H(k_opad, sizeof(k_opad), ihash, sizeof(ihash), ohash, sizeof(ohash));
  sz = (outlen > SHA256_HASH_SIZE) ? SHA256_HASH_SIZE : outlen;
  memcpy(out, ohash, sz);
  return sz;
}

static void* H(const void* x,
               const size_t xlen,
               const void* y,
               const size_t ylen,
               void* out,
               const size_t outlen) {
  void* result;
  size_t buflen = (xlen + ylen);
  uint8_t* buf = (uint8_t*)malloc(buflen);
  init_sha_context();
  uint8_t hash[SHA256_HASH_SIZE];

  memcpy(buf, x, xlen);
  memcpy(buf + xlen, y, ylen);
  // do hash
#ifdef gladman_sha
    sha256(hash, buf, buflen, cx);
#endif
#ifdef saddi_sha
    sha256_update (&ctx, buf, buflen);
    sha256_final (&ctx, hash);
#endif
#ifdef mbedtls_sha
    mbedtls_sha256(buf, buflen, hash, 0, ctx);
#endif

  size_t sz = (outlen > SHA256_HASH_SIZE) ? SHA256_HASH_SIZE : outlen;
  result = memcpy(out, hash, sz);
  free(buf);
  return result;
}



//static void* sha(const void* data,
//                    const size_t datalen,
//                    void* out,
//                    const size_t outlen) {
//  size_t sz;
//  Sha256Context ctx;
//  SHA256_HASH hash;
//
//  Sha256Initialise(&ctx);
//  Sha256Update(&ctx, data, datalen);
//  Sha256Finalise(&ctx, &hash);
//
//  sz = (outlen > SHA256_HASH_SIZE) ? SHA256_HASH_SIZE : outlen;
//  return memcpy(out, hash.bytes, sz);
//}
