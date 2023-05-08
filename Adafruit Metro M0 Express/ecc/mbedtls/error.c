/*
 *  Error message information
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "common.h"

#include "error.h"

#if defined(MBEDTLS_ERROR_C) || defined(MBEDTLS_ERROR_STRERROR_DUMMY)

#if defined(MBEDTLS_ERROR_C)

#if defined(MBEDTLS_PLATFORM_C)
#include "platform.h"
#else
#define mbedtls_snprintf snprintf
#endif

#include <stdio.h>
#include <string.h>

#if defined(MBEDTLS_BIGNUM_C)
#include "bignum.h"
#endif

#if defined(MBEDTLS_ECP_C)
#include "ecp.h"
#endif

#if defined(MBEDTLS_ERROR_C)
#include "error.h"
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "platform.h"
#endif

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif



const char * mbedtls_high_level_strerr( int error_code )
{
    int high_level_error_code;

    if( error_code < 0 )
        error_code = -error_code;

    /* Extract the high-level part from the error code. */
    high_level_error_code = error_code & 0xFF80;

    switch( high_level_error_code )
    {
        /* Begin Auto-Generated Code. */

#if defined(MBEDTLS_ECP_C)
        case -(MBEDTLS_ERR_ECP_BAD_INPUT_DATA):
            return( "ECP - Bad input parameters to function" );
        case -(MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL):
            return( "ECP - The buffer is too small to write to" );
        case -(MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE):
            return( "ECP - The requested feature is not available, for example, the requested curve is not supported" );
        case -(MBEDTLS_ERR_ECP_VERIFY_FAILED):
            return( "ECP - The signature is not valid" );
        case -(MBEDTLS_ERR_ECP_ALLOC_FAILED):
            return( "ECP - Memory allocation failed" );
        case -(MBEDTLS_ERR_ECP_RANDOM_FAILED):
            return( "ECP - Generation of random value, such as ephemeral key, failed" );
        case -(MBEDTLS_ERR_ECP_INVALID_KEY):
            return( "ECP - Invalid private or public key" );
        case -(MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH):
            return( "ECP - The buffer contains a valid signature followed by more data" );
        case -(MBEDTLS_ERR_ECP_IN_PROGRESS):
            return( "ECP - Operation in progress, call again with the same parameters to continue" );
#endif /* MBEDTLS_ECP_C */
        /* End Auto-Generated Code. */

        default:
            break;
    }

    return( NULL );
}

const char * mbedtls_low_level_strerr( int error_code )
{
    int low_level_error_code;

    if( error_code < 0 )
        error_code = -error_code;

    /* Extract the low-level part from the error code. */
    low_level_error_code = error_code & ~0xFF80;

    switch( low_level_error_code )
    {
        /* Begin Auto-Generated Code. */

#if defined(MBEDTLS_BIGNUM_C)
        case -(MBEDTLS_ERR_MPI_FILE_IO_ERROR):
            return( "BIGNUM - An error occurred while reading from or writing to a file" );
        case -(MBEDTLS_ERR_MPI_BAD_INPUT_DATA):
            return( "BIGNUM - Bad input parameters to function" );
        case -(MBEDTLS_ERR_MPI_INVALID_CHARACTER):
            return( "BIGNUM - There is an invalid character in the digit string" );
        case -(MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
            return( "BIGNUM - The buffer is too small to write to" );
        case -(MBEDTLS_ERR_MPI_NEGATIVE_VALUE):
            return( "BIGNUM - The input arguments are negative or result in illegal output" );
        case -(MBEDTLS_ERR_MPI_DIVISION_BY_ZERO):
            return( "BIGNUM - The input argument for division is zero, which is not allowed" );
        case -(MBEDTLS_ERR_MPI_NOT_ACCEPTABLE):
            return( "BIGNUM - The input arguments are not acceptable" );
        case -(MBEDTLS_ERR_MPI_ALLOC_FAILED):
            return( "BIGNUM - Memory allocation failed" );
#endif /* MBEDTLS_BIGNUM_C */

#if defined(MBEDTLS_ERROR_C)
        case -(MBEDTLS_ERR_ERROR_GENERIC_ERROR):
            return( "ERROR - Generic error" );
        case -(MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED):
            return( "ERROR - This is a bug in the library" );
#endif /* MBEDTLS_ERROR_C */

#if defined(MBEDTLS_PLATFORM_C)
        case -(MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED):
            return( "PLATFORM - Hardware accelerator failed" );
        case -(MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED):
            return( "PLATFORM - The requested feature is not supported by the platform" );
#endif /* MBEDTLS_PLATFORM_C */

#if defined(MBEDTLS_THREADING_C)
        case -(MBEDTLS_ERR_THREADING_BAD_INPUT_DATA):
            return( "THREADING - Bad input parameters to function" );
        case -(MBEDTLS_ERR_THREADING_MUTEX_ERROR):
            return( "THREADING - Locking / unlocking / free failed with error code" );
#endif /* MBEDTLS_THREADING_C */
        /* End Auto-Generated Code. */

        default:
            break;
    }

    return( NULL );
}

void mbedtls_strerror( int ret, char *buf, size_t buflen )
{
    size_t len;
    int use_ret;
    const char * high_level_error_description = NULL;
    const char * low_level_error_description = NULL;

    if( buflen == 0 )
        return;

    memset( buf, 0x00, buflen );

    if( ret < 0 )
        ret = -ret;

    if( ret & 0xFF80 )
    {
        use_ret = ret & 0xFF80;

        // Translate high level error code.
        high_level_error_description = mbedtls_high_level_strerr( ret );

        if( high_level_error_description == NULL )
            mbedtls_snprintf( buf, buflen, "UNKNOWN ERROR CODE (%04X)", (unsigned int) use_ret );
        else
            mbedtls_snprintf( buf, buflen, "%s", high_level_error_description );
    }

    use_ret = ret & ~0xFF80;

    if( use_ret == 0 )
        return;

    // If high level code is present, make a concatenation between both
    // error strings.
    //
    len = strlen( buf );

    if( len > 0 )
    {
        if( buflen - len < 5 )
            return;

        mbedtls_snprintf( buf + len, buflen - len, " : " );

        buf += len + 3;
        buflen -= len + 3;
    }

    // Translate low level error code.
    low_level_error_description = mbedtls_low_level_strerr( ret );

    if( low_level_error_description == NULL )
        mbedtls_snprintf( buf, buflen, "UNKNOWN ERROR CODE (%04X)", (unsigned int) use_ret );
    else
        mbedtls_snprintf( buf, buflen, "%s", low_level_error_description );
}

#else /* MBEDTLS_ERROR_C */

/*
 * Provide an non-function in case MBEDTLS_ERROR_C is not defined
 */
void mbedtls_strerror( int ret, char *buf, size_t buflen )
{
    ((void) ret);

    if( buflen > 0 )
        buf[0] = '\0';
}

#endif /* MBEDTLS_ERROR_C */

#if defined(MBEDTLS_TEST_HOOKS)
void (*mbedtls_test_hook_error_add)( int, int, const char *, int );
#endif

#endif /* MBEDTLS_ERROR_C || MBEDTLS_ERROR_STRERROR_DUMMY */
