/* Uncomment UART_LED to select test UART+LED Blink*/
//#define UART_LED

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
void UART1_putchar(char c) {

    //Load data onto buffer
    USCI_A_UART_transmitData(USCI_A1_BASE, c);
    //Wait for transmit buffer to be empty
    while(USCI_A_UART_queryStatusFlags(USCI_A1_BASE, USCI_A_UART_BUSY)){};

}

/*  Function to send a string through UART by sending each character in the string. */
void UART1_puts(char* s) {
    while (*s != 0)             /* if not end of string */
    UART1_putchar(*s++);        /* send the character through UART0 */
}
#endif
/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/* LED */
	P1DIR |= BIT0;
    P1OUT &= 0x0;

#ifdef UART_LED

	 //P4.4,5 = USCI_A1 TXD/RXD for MSP430F5529
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN4 + GPIO_PIN5
        );

    //Baudrate = 9600, clock freq = 1.048MHz
    //UCBRx = 109, UCBRFx = 0, UCBRSx = 2, UCOS16 = 0
    // N = clock freq/Baudrate
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 109;
    param.firstModReg = 0;
    param.secondModReg = 2;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    //Check UART initialization
    if (STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param)){
            return;
        }

    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A1_BASE);

      char buffer[20];
#endif

      while(1)
      {
          P1OUT ^= 0x01;    //toggle LED

          for(i=10000; i>0; i--);    //delay

#ifdef UART_LED
          sprintf(buffer, "Value: %d\n", --transmitData);
          UART1_puts(buffer);
#endif

      }
}
