/**************************************************************************/
/*!
    @file     rsa.h
    @author   Kyle Loudon
              modified: microBuilder.eu
    @date     4 January, 2010
    @version  1.0

    Basic RSA-encryption using 64-bit math (32-bit keys).

    Based on the examples from "Mastering Algorithms with C" by
    Kyle Loudon (O'Reilly, 1999).
*/
/**************************************************************************/

#ifndef _RSA_H_
#define _RSA_H_

#include <stdint.h>

typedef uint64_t huge_t;

/* Structure for RSA public keys. */
typedef struct rsaPubKey_s
{
    huge_t e;
    huge_t n;
}
        rsaPubKey_t;

/* Define a structure for RSA private keys. */
typedef struct rsaPriKey_s
{
    huge_t d;
    huge_t n;
}
        rsaPriKey_t;

void rsaTest();
void rsaEncrypt(huge_t plaintext, huge_t *ciphertext, rsaPubKey_t pubkey);
void rsaDecrypt(huge_t ciphertext, huge_t *plaintext, rsaPriKey_t prikey);

#endif