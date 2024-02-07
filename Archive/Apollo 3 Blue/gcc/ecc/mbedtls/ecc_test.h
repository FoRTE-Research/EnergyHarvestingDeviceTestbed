
#ifndef MBEDTLS_TEST_ECDH_ECC_TEST_H
#define MBEDTLS_TEST_ECDH_ECC_TEST_H

void mbedtls_init(unsigned char *prv_a, unsigned char *prv_b, unsigned char *cli_srv_x, unsigned char *cli_srv_y, unsigned char *srv_cli_x, unsigned char *srv_cli_y);
int mbedtls_compute_shared();
int mbedtls_check_result();


#endif //MBEDTLS_TEST_ECDH_ECC_TEST_H
