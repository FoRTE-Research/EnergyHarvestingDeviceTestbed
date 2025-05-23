#include "hmac_sha256.h"

/** need to uncomment if the board you are using is MSP432P401R **/
#define msp432p401r

#ifdef msp432p401r
#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#include "sha/experiment_time.h"
#endif

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SHA256_HASH_SIZE 32

int main() {
#ifdef msp432p401r
    /** Initialize the board **/
    board_init();

    /** Starting the timer to measure elapsed time **/
    startTimer();
#endif

    const char* str_data = "Hello World!";
    const char* str_key = "super-secret-key";
    uint8_t out[SHA256_HASH_SIZE];
    char out_str[SHA256_HASH_SIZE * 2 + 1];
    unsigned i;

    // Call hmac-sha function
    hmac_sha256(str_key, strlen(str_key), str_data, strlen(str_data), &out,
                sizeof(out));

#ifdef msp432p401r
    volatile unsigned int elapsed = getElapsedTime();
#endif

    // Convert `out` to string with printf
    memset(&out_str, 0, sizeof(out_str));
    for (i = 0; i < sizeof(out); i++) {
        snprintf(&out_str[i*2], 3, "%02x", out[i]);
    }

//     Print out the result
    printf("Message: %s\n", str_data);
    printf("Key: %s\n", str_key);
    printf("HMAC: %s\n", out_str);

    // This assertion fails if something went wrong
    assert(strncmp(
            out_str,
            "4b393abced1c497f8048860ba1ede46a23f1ff5209b18e9c428bddfbb690aad8",
            SHA256_HASH_SIZE * 2) == 0);

    while(1);
}

//=========================================================================================================
//#include "chez/hmac_sha256.h"
//
//int main() {
//    char* str_data = "Hello World!";
//    char* str_key = "super-secret-key";
//
//    hs256(str_data, str_key);
//}


//0xe097fffaa0
//0xe097fffa80

//0xe8497ff890
