//
// Created by willi on 2022/2/22.
//

#ifndef TINY_BIGNUM_RSA_RSA_TEST_H
#define TINY_BIGNUM_RSA_RSA_TEST_H

#include "bn.h"

void pow_mod_faster(struct bn* a, struct bn* b, struct bn* n, struct bn* res);
void rsa1024_encrypt(char *public, char *private, char *buff, int x);
void rsa1024_decrypt(char *public, char *private, char *buff, int x);

#endif //TINY_BIGNUM_RSA_RSA_TEST_H
