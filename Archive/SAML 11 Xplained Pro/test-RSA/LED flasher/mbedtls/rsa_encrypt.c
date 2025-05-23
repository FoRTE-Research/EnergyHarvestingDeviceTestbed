///*
 //*  RSA simple data encryption program
 //*
 //*  Copyright The Mbed TLS Contributors
 //*  SPDX-License-Identifier: Apache-2.0
 //*
 //*  Licensed under the Apache License, Version 2.0 (the "License"); you may
 //*  not use this file except in compliance with the License.
 //*  You may obtain a copy of the License at
 //*
 //*  http://www.apache.org/licenses/LICENSE-2.0
 //*
 //*  Unless required by applicable law or agreed to in writing, software
 //*  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 //*  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 //*  See the License for the specific language governing permissions and
 //*  limitations under the License.
 //*/
//
//#include "build_info.h"
////#include "msp.h"
//
//#if defined(MBEDTLS_PLATFORM_C)
//#include "platform.h"
//#else
//#include <stdio.h>
//#include <stdlib.h>
//#define mbedtls_fprintf         fprintf
//#define mbedtls_printf          printf
//#define mbedtls_exit            exit
//#define MBEDTLS_EXIT_SUCCESS    EXIT_SUCCESS
//#define MBEDTLS_EXIT_FAILURE    EXIT_FAILURE
//#endif /* MBEDTLS_PLATFORM_C */
//
//#if defined(MBEDTLS_BIGNUM_C) && defined(MBEDTLS_RSA_C) && \
        //defined(MBEDTLS_ENTROPY_C) && defined(MBEDTLS_FS_IO) && \
        //defined(MBEDTLS_CTR_DRBG_C)
//#include "rsa.h"
//#include "entropy.h"
//#include "ctr_drbg.h"
//
//#include <string.h>
//#endif
//
//#if !defined(MBEDTLS_BIGNUM_C) || !defined(MBEDTLS_RSA_C) ||  \
        //!defined(MBEDTLS_ENTROPY_C) || !defined(MBEDTLS_FS_IO) || \
        //!defined(MBEDTLS_CTR_DRBG_C)
//int main( void )
//{
    //mbedtls_printf("MBEDTLS_BIGNUM_C and/or MBEDTLS_RSA_C and/or "
            //"MBEDTLS_ENTROPY_C and/or MBEDTLS_FS_IO and/or "
            //"MBEDTLS_CTR_DRBG_C not defined.\n");
    //mbedtls_exit( 0 );
//}
//#else
//
//
//int main( int argc, char *argv[] )
//{
    //argv[0] = "54321";
    //argc = 2;
    //FILE *f;
    //int ret = 1;
    //int exit_code = MBEDTLS_EXIT_FAILURE;
    //size_t i;
    //mbedtls_rsa_context rsa;
    //mbedtls_entropy_context entropy;
    //mbedtls_ctr_drbg_context ctr_drbg;
    //unsigned char input[1024];
    //unsigned char buf[512];
    //const char *pers = "rsa_encrypt";
    //mbedtls_mpi N, E;
    //char n = "AE1EC41FDD978C18CB43F9587F9B85DF804603100611497DCB445D157E44E717C78D53FAC3644DEA302645F6CFF852A785C3DAEA525BE01A4B1960D6512D97C677436ED17D03A55DDD8E41D737456C2B1512D533806EB048C5570269CBDFABB5E335821CE69C892A825A3896FC46990A8F6FECC759DAD9D6FD76BBF55BAA34B0789CACE898B6CC8CDBB50A0BFE7073A31DAF0B67845F76B71D42942B03FC02D6D68789C6CEF502C39AA0FB392E5E84BD1581E7295BDF6C45463FEA20A5220413381B82A72F95B1BB29AC6E833B70EB5B9F9D43B4D56A94ECBD02C1CBC8C8EED903485BD2A379A8B81B8FE20216EE6019A5F19656A483CCD9C23EB3B17678050B";
    //char e = "010001";
//
    //if( argc != 2 )
    //{
        //mbedtls_printf( "usage: rsa_encrypt <string of max 100 characters>\n" );
//
//#if defined(_WIN32)
        //mbedtls_printf( "\n" );
//#endif
//
        //mbedtls_exit( exit_code );
    //}
//
    //mbedtls_printf( "\n  . Seeding the random number generator..." );
    //fflush( stdout );
//
    //mbedtls_mpi_init( &N ); mbedtls_mpi_init( &E );
    //mbedtls_rsa_init( &rsa );
    //mbedtls_ctr_drbg_init( &ctr_drbg );
    //mbedtls_entropy_init( &entropy );
//
    //ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func,
                                 //&entropy, (const unsigned char *) pers,
                                 //strlen( pers ) );
//
    //if( ret != 0 )
    //{
        //mbedtls_printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n",
                        //ret );
        //goto exit;
    //}
//
    //mbedtls_mpi_read_string( &N, 16, n );
    //mbedtls_mpi_read_string( &E, 16, e );
    ////    mbedtls_printf( "\n  . Reading public key from rsa_pub.txt" );
    ////    fflush( stdout );
    ////
    ////    if( ( f = fopen( "rsa_pub.txt", "rb" ) ) == NULL )
    ////    {
    ////        mbedtls_printf( " failed\n  ! Could not open rsa_pub.txt\n" \
    ////                "  ! Please run rsa_genkey first\n\n" );
    ////        goto exit;
    ////    }
    ////
    ////    if( ( ret = mbedtls_mpi_read_file( &N, 16, f ) ) != 0 ||
    ////        ( ret = mbedtls_mpi_read_file( &E, 16, f ) ) != 0 )
    ////    {
    ////        mbedtls_printf( " failed\n  ! mbedtls_mpi_read_file returned %d\n\n",
    ////                        ret );
    ////        fclose( f );
    ////        goto exit;
    ////    }
    ////    fclose( f );
//
    //if( ( ret = mbedtls_rsa_import( &rsa, &N, NULL, NULL, NULL, &E ) ) != 0 )
    //{
        //mbedtls_printf( " failed\n  ! mbedtls_rsa_import returned %d\n\n",
                        //ret );
        //goto exit;
    //}
//
    //if( strlen( argv[1] ) > 100 )
    //{
        //mbedtls_printf( " Input data larger than 100 characters.\n\n" );
        //goto exit;
    //}
//
    //memcpy( input, argv[1], strlen( argv[1] ) );
//
    ///*
     //* Calculate the RSA encryption of the hash.
     //*/
    //mbedtls_printf( "\n  . Generating the RSA encrypted value" );
    //fflush( stdout );
//
    //ret = mbedtls_rsa_pkcs1_encrypt( &rsa, mbedtls_ctr_drbg_random,
                                     //&ctr_drbg, strlen( argv[1] ), input, buf );
    //if( ret != 0 )
    //{
        //mbedtls_printf( " failed\n  ! mbedtls_rsa_pkcs1_encrypt returned %d\n\n",
                        //ret );
        //goto exit;
    //}
//
    ///*
     //* Write the signature into result-enc.txt
     //*/
    //if( ( f = fopen( "result-enc.txt", "wb+" ) ) == NULL )
    //{
        //mbedtls_printf( " failed\n  ! Could not create %s\n\n", "result-enc.txt" );
        //goto exit;
    //}
//
    //for( i = 0; i < rsa.MBEDTLS_PRIVATE(len); i++ )
        //mbedtls_fprintf( f, "%02X%s", buf[i],
                         //( i + 1 ) % 16 == 0 ? "\r\n" : " " );
//
    //fclose( f );
//
    //mbedtls_printf( "\n  . Done (created \"%s\")\n\n", "result-enc.txt" );
//
    //exit_code = MBEDTLS_EXIT_SUCCESS;
//
    //exit:
    //mbedtls_mpi_free( &N ); mbedtls_mpi_free( &E );
    //mbedtls_ctr_drbg_free( &ctr_drbg );
    //mbedtls_entropy_free( &entropy );
    //mbedtls_rsa_free( &rsa );
//
//#if defined(_WIN32)
    //mbedtls_printf( "  + Press Enter to exit this program.\n" );
    //fflush( stdout ); getchar();
//#endif
//
    //mbedtls_exit( exit_code );
//}
//#endif /* MBEDTLS_BIGNUM_C && MBEDTLS_RSA_C && MBEDTLS_ENTROPY_C &&
          //MBEDTLS_FS_IO && MBEDTLS_CTR_DRBG_C */
