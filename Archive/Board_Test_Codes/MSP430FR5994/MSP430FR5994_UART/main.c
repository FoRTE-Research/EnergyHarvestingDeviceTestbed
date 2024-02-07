/* Uncomment UART_LED to select test UART+LED Blink*/
#define UART_LED

#include <msp430.h> 
#include <stdio.h>
#include <stdint.h>


#ifdef UART_LED
#include "driverlib.h"
uint8_t transmitData = 255;
#endif

volatile uint32_t i;

#ifdef UART_LED
/*  Function to send a character through UART*/
void UART0_putchar(char c) {

    //Load data onto buffer
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, c);
    //Wait for transmit buffer to be empty
    while(EUSCI_A_UART_queryStatusFlags(EUSCI_A0_BASE, EUSCI_A_UART_BUSY)){};
}

/*  Function to send a string through UART by sending each character in the string. */
void UART0_puts(char* s) {
    while (*s != 0)             /* if not end of string */
    UART0_putchar(*s++);        /* send the character through UART0 */
}
#endif
/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
	                                                    // to activate previously configured port settings
	/* LED */
	P1OUT = 0x0;
    P1DIR = 0x7; // setup pin direction to output

#ifdef UART_LED
	// LFXT Setup - LFXT oscillator supports ultra-low-current consumption using a 32768-Hz watch crystal.
    //Set PJ.4 and PJ.5 as Primary Module Function Input.
    /*

    * Select Port J
    * Set Pin 4, 5 to input Primary Module Function, LFXT. A watch crystal connects to LFXIN & LFXOUT pins when enabled for LFXT configuration.
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 + GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    //ACLK = BRCLK = 32.768kHz, MCLK = SMCLK = DCO = ~1MHz
    //Code works by configuring just the ACLK and LFXT as well.
    //Set DCO frequency to 1 MHz
    CS_setDCOFreq(CS_DCORSEL_0,CS_DCOFSEL_0);
    //Set external clock frequency to 32.768 KHz
    CS_setExternalClockSource(32768,0);
	//Set ACLK=LFXT
    CS_initClockSignal(CS_ACLK,CS_LFXTCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
	//Start XT1 with no time out
    CS_turnOnLFXT(CS_LFXT_DRIVE_0);

    //Configure UART pins
    //Set P2.0 and P2.1 as Secondary Module Function Input for MSP430FR5994.
    /*

    * Select Port 2d
    * Set Pin 0, 1 to input Secondary Module Function, (UCA0TXD/UCA0SIMO, UCA0RXD/UCA0SOMI).
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P2,
    GPIO_PIN0 + GPIO_PIN1,
    GPIO_SECONDARY_MODULE_FUNCTION
    );

    // Configure UART 9600 baud rate with ACLK = LFXT = 32.768kHz
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 92;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
        return;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    char buffer[20];
#endif

    while (1)
    {
        P1OUT ^= 0x7; // toggle LED

        for(i=10000; i>0; i--);    //delay

#ifdef UART_LED
        sprintf(buffer, "Value: %d\n", --transmitData);
        UART0_puts(buffer);
#endif
    }

//	return 0;
}
