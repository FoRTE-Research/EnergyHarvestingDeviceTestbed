/* Uncomment UART_LED to select test UART+LED Blink*/
#define UART_LED

#include "msp432.h"


#ifdef UART_LED
#include "driverlib.h"
#endif

/* Standard Includes */
#include <stdint.h>

#include <stdbool.h>
#include <stdio.h>

uint8_t transmitData = 255;
volatile uint32_t i;

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 9600 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 *http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */

#ifdef UART_LED

const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void UART0_putchar(char c) {
    MAP_UART_transmitData(EUSCI_A0_BASE, c);              /* send a char */

    while(UART_queryStatusFlags(EUSCI_A0_BASE, EUSCI_A_UART_BUSY));  /* wait for transmit buffer empty */
}

void UART0_puts(char* s) {
    while (*s != 0)             /* if not end of string */
    UART0_putchar(*s++);        /* send the character through UART0 */
}

#endif

int main(void)
{
    /* Halting WDT using Driverlib */
//    MAP_WDT_A_holdTimer();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer.

    /* LED */
    P1OUT |= 0x0;
    P1DIR |= 0x1; // setup pin direction to output

#ifdef UART_LED
    /* UART */
    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    char buffer[20];
#endif
    while(1)
    {
        P1OUT ^= 0x1; // toggle LED

        for(i=100000; i>0; i--);    //delay

#ifdef UART_LED
        sprintf(buffer, "Value: %d\n", --transmitData);
        UART0_puts(buffer);
#endif

    }
}

