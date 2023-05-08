#ifndef AES_TEST_H_
#define AES_TEST_H_

/** need to choose which AES implementation to run **/
#define gladman_aes
//#define slow_tiny_aes
//#define tiny_aes
//#define mbedtls_aes

/** need to uncomment if the board you are using is MSP432P401R **/
//#define msp432p401r
//#define msp430g2553
#define msp430fr5994
//#define riscv

///** need to define key size **/
#define AES_128 1
//#define AES_192 1
//#define AES_256 1

/** can define block chaining **/
#define AES_CBC
#define MSG_LNGTH 1024

/** AES constants **/
#define AES_BLOCK_SIZE_BITS 128
#define AES_BLOCK_SIZE_BYTES (AES_BLOCK_SIZE_BITS/8)

// Stop watchdog timer
#if defined(msp430g2553)
    #define board_init()    WDTCTL = WDTPW | WDTHOLD
#endif
#if defined(msp430fr5994)
    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    #define board_init()    WDTCTL = WDTPW | WDTHOLD; PM5CTL0 &= ~LOCKLPM5
#endif
#ifdef msp432p401r
    #define board_init() WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD
#endif

#endif /* AES_TEST_H_ */
