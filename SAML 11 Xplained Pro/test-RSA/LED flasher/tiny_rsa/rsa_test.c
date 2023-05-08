//
// Created by willi on 2022/2/22.
// This file contains functions that have been extracted from rsa.c of tiny RSA.
// The function names have been modified from the original rsa.c.
//

#include "bn.h"

/* O(log n) */
void pow_mod_faster(struct bn* a, struct bn* b, struct bn* n, struct bn* res)
{
    bignum_from_int(res, 1); /* r = 1 */

    struct bn tmpa;
    struct bn tmpb;
    struct bn tmp;
    bignum_assign(&tmpa, a);
    bignum_assign(&tmpb, b);

    while (1)
    {
        if (tmpb.array[0] & 1)     /* if (b % 2) */
        {
            bignum_mul(res, &tmpa, &tmp);  /*   r = r * a % m */
            bignum_mod(&tmp, n, res);
        }
        bignum_rshift(&tmpb, &tmp, 1); /* b /= 2 */
        bignum_assign(&tmpb, &tmp);

        if (bignum_is_zero(&tmpb))
            break;

        bignum_mul(&tmpa, &tmpa, &tmp);
        bignum_mod(&tmp, n, &tmpa);
    }
}

void rsa1024_encrypt(char *public, char *private, char *buff, int x)
{

    char buf[8192];

    struct bn n; /* public  key */
    struct bn d; /* private key */
    struct bn e; /* public exponent */
    struct bn m; /* clear text message */
    struct bn c; /* cipher text */

//    int len_pub = strlen(public);
//    int len_prv = strlen(private);

    bignum_init(&n);
    bignum_init(&d);
    bignum_init(&e);
    bignum_init(&m);
    bignum_init(&c);

    bignum_from_string(&n, public,  256);
    bignum_from_string(&d, private, 256);
    bignum_from_int(&e, 65537);
    bignum_init(&m);
    bignum_init(&c);

    bignum_from_int(&m, x);
    bignum_to_string(&m, buf, sizeof(buf));

    /** Encrypting **/
    pow_mod_faster(&m, &e, &n, &c);
    bignum_to_string(&c, buf, sizeof(buf));

    for(int i = 0; i < sizeof(buf); i++) {
        buff[i] = buf[i];
    }

}

void rsa1024_decrypt(char *public, char *private, char *buff, char *cipher)
{

    char buf[8192];

    struct bn n; /* public  key */
    struct bn d; /* private key */
    struct bn m; /* clear text message */
    struct bn c; /* cipher text */

    //int len_pub = strlen(public);
    //int len_prv = strlen(private);

    bignum_init(&n);
    bignum_init(&d);
    bignum_init(&m);
    bignum_init(&c);

    bignum_from_string(&n, public,  256);
    bignum_from_string(&d, private, 256);
    bignum_from_string(&c, cipher, 256);

    pow_mod_faster(&c, &d, &n, &m);
    bignum_to_string(&m, buf, sizeof(buf));

    for(int i = 0; i < sizeof(buf); i++) {
        buff[i] = buf[i];
    }
}
