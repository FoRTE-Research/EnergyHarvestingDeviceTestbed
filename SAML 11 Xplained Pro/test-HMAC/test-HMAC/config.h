//
// Created by william on 2022/4/2.
//

#ifndef HMAC_256_CONFIG_H
#define HMAC_256_CONFIG_H

//HMAC sha base
//#define gladman_sha
//#define saddi_sha
#define mbedtls_sha

/** need to choose which AES implementation to run **/
//#define gladman_cmac
//#define tiny_cmac
//#define mbedtls_cmac

/** AES constants **/
//#define AES_BLOCK_SIZE_BITS 128
//#define AES_BLOCK_SIZE_BYTES (AES_BLOCK_SIZE_BITS/8)


#endif //HMAC_256_CONFIG_H
