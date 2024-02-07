/*
 *  Example Elliptic Curve Diffie-Hellman (ECDH) key exchange program
 *
 *  This file is a modification of the ecdh_curve25519.c example which ships with mbedTLS to use different curves
 *
 * Curve25519 is very fast, but only uses 256 bits (128 bits of security) even though it is highly respected as being
 * safe by pretty much everyone.  This curve is suitable for an asymmetric ECDH key exchange used to derive a 128-bit
 * key for use with a symmetric cipher such as AES-128. Python's Cryptography module doesn't have support for curve25519
 * until version 2.0 and even then it only supports it with a bleeding-edge version of OpenSSL.
 *
 * Elliptic Curve SECP384R1 is a 384-bit NIST curve over a prime field.  This is a curve with intermediate performance
 * and intermediate security.  It should be suitable for an asymmetric ECDH key exchange used to derive a 192-bit key
 * for use with a symmetric cipher such as AES-192.  Python's Cryptography module has support for this curve in all
 * recent versions.  The "SafeCurves" website specifically marks this curve as unsafe.  NSA "Suite B" includes this
 * curve in the list of recommended curves.
 *
 * Elliptic Curve SECP521R1 is a 521-bit NIST curve over a prime field.  This is slower than most other recommended
 * curves due to the larger bit size, but should be very secure and suitable for an asymmetric ECDH key exchange used to
 * derive a 256-bit key for use with a symmetric cipher such as AES-256.  Python's Cryptography module has support for
 * this curve in all recent versions.  The "SafeCurves" website doesn't comment on this particular NIST curve in any
 * way shape or form.  Notably, this particular NIST curve is not included in the "NSA Suite B" set of recommended
 * curves, ostensibly because Suite B was only shooting for 192 bits of security and this curve would be overkill for
 * that.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "platform.h"
#else
#include <stdio.h>
#define mbedtls_printf     printf
#endif

#include "ecc_test.h"
#include "../curve.h"
#include "ecdh.h"
#include "ecp.h"
#include "error.h"

mbedtls_ecdh_context ctx_cli, ctx_srv;
unsigned char *priv_a;
unsigned char *priv_b;
unsigned char *cli_to_srv_x_inner;
unsigned char *cli_to_srv_y_inner;
unsigned char *srv_to_cli_x_inner;
unsigned char *srv_to_cli_y_inner;

void mbedtls_init(unsigned char *prv_a, unsigned char *prv_b, unsigned char *cli_srv_x, unsigned char *cli_srv_y, unsigned char *srv_cli_x, unsigned char *srv_cli_y) {

    priv_a = prv_a;
    priv_b = prv_b;
    cli_to_srv_x_inner = cli_srv_x;
    cli_to_srv_y_inner = cli_srv_y;
    srv_to_cli_x_inner = srv_cli_x;
    srv_to_cli_y_inner = srv_cli_y;

    mbedtls_ecdh_init( &ctx_cli );
    mbedtls_ecdh_init( &ctx_srv );

    // Set a group (in the abstract algebra sense) using well-known domain parameters - configure elliptic curve used
    mbedtls_ecp_group_load( &ctx_cli.grp,     // Destination group
                                  ELLIPTIC_CURVE ); // Index in the list of well-known domain parameters

    mbedtls_mpi_read_binary( &ctx_cli.d,   // Destination MPI
                             priv_a,    // Input buffer
                             BUF_BYTES );     // Input buffer size
    mbedtls_mpi_read_binary( &ctx_cli.Q.X,   // Destination MPI
                             cli_to_srv_x_inner,    // Input buffer
                             BUF_BYTES );     // Input buffer size
    mbedtls_mpi_read_binary( &ctx_cli.Q.Y,   // Destination MPI
                             cli_to_srv_y_inner,    // Input buffer
                             BUF_BYTES );     // Input buffer size

    mbedtls_ecp_group_load( &ctx_srv.grp, ELLIPTIC_CURVE );

    mbedtls_mpi_read_binary( &ctx_srv.d,   // Destination MPI
                             priv_b,    // Input buffer
                             BUF_BYTES );     // Input buffer size
    mbedtls_mpi_read_binary( &ctx_srv.Q.X,   // Destination MPI
                             srv_to_cli_x_inner,    // Input buffer
                             BUF_BYTES );     // Input buffer size
    mbedtls_mpi_read_binary( &ctx_srv.Q.Y,   // Destination MPI
                             srv_to_cli_y_inner,    // Input buffer
                             BUF_BYTES );     // Input buffer size

    // Set the Z component of the peer's public value (public key) to 1
    mbedtls_mpi_lset( &ctx_srv.Qp.Z,1 );            // Value to use

    // Set the X component of the peer's public value based on what was passed from client in the buffer
    mbedtls_mpi_read_binary( &ctx_srv.Qp.X, cli_to_srv_x_inner, BUF_BYTES );     // Input buffer size

    // Set the Y component of the peer's public value based on what was passed from client in the buffer
    mbedtls_mpi_read_binary( &ctx_srv.Qp.Y, cli_to_srv_y_inner, BUF_BYTES );     // Input buffer size
}

int mbedtls_compute_shared()
{
    int ret;

    // Compute shared secret
    mbedtls_ecdh_compute_shared( &ctx_srv.grp,            // ECP group
                                   &ctx_srv.z,              // Destination MPI (shared secret)
                                   &ctx_srv.Qp,             // Public key from other party
                                   &ctx_srv.d,              // Our secret exponent (private key)
                                   NULL, // RNG function - countermeasure against timing attacks
                                   NULL );             // RNG parameter

    mbedtls_mpi_lset( &ctx_cli.Qp.Z, 1 );

    mbedtls_mpi_read_binary( &ctx_cli.Qp.X, srv_to_cli_x_inner, BUF_BYTES );

    mbedtls_mpi_read_binary( &ctx_cli.Qp.Y, srv_to_cli_y_inner, BUF_BYTES );


    mbedtls_ecdh_compute_shared( &ctx_cli.grp, &ctx_cli.z, &ctx_cli.Qp, &ctx_cli.d, NULL, NULL);

    return 1;
}

int mbedtls_check_result(){
    int ret;
    ret = mbedtls_mpi_cmp_mpi( &ctx_cli.z, &ctx_srv.z );
    printf( " ok\n" );
    mbedtls_ecdh_free( &ctx_srv );
    mbedtls_ecdh_free( &ctx_cli );
    return( ret != 0 );
}
