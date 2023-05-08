#include <string.h>

/** need to uncomment if the board you are using **/
//#define msp432p401r
//#define msp430g2553
#define msp430fr5994
//#define riscv

#ifdef msp432p401r
#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#include "../experiment_time.h"
#endif

#if defined msp430g2553 || defined msp430f5529 || defined msp430fr5994
#include "msp430.h"
#include "experiment_time.h"
#endif

#include "cmac.h"
#include "utils.h"

int main()
{
#if defined msp432p401r || defined msp430fr5994 || defined msp430f5529
    /** Initialize the board **/
    board_init();

    /** Starting the timer to measure elapsed time **/
    startTimer();
#endif

    unsigned char key[] = { 0x31, 0x50, 0x10, 0x47, 0x17, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    unsigned char message[] =
    { "Information Security is a multidisciplinary area of study and professional activity which is concerned with the development and implementation of security mechanisms of all available types (technical, organizational, human-oriented and legal) to keep information in all its locations (within and outside the organization's perimeter) and, consequently, information systems, where information is created, processed, stored, transmitted and destroyed, free from threats. This project is finished by GUORUI XU." };

    unsigned char out[16];

    aes_cmac(message, strlen((char*) message) + 1, (unsigned char*) out, key);
    //    printf("%sAES-128-CMAC Result%s\n", ACCENTCOLOR, DEFAULT);
    //    print_bytes(out, 16);

#if defined msp432p401r || defined msp430fr5994 || defined msp430f5529
    volatile unsigned int elapsed = getElapsedTime();
#endif
    while (1);
}

