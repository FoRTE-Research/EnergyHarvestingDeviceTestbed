## HW1: Blinky

1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP430G2553** as the **Target**
5. Type in a name for the project
6. Select **Blink The LED** from **Basic Examples**
7. Click **Finish**
8. Your source code should look like the following:
```
#include <msp430.h>				


/**
 * blink.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;					// configure P1.0 as output

	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
		P1OUT ^= 0x01;				// toggle P1.0
		for(i=10000; i>0; i--);     // delay
	}
}
```
9. Connect the board to the host using the provided USB cable
10. Press the button that looks like a Folder with curly braces to Flash the program.
11. After a few moments, the LED should blink.

## HW2: Hello World
1. Start CCS
2. Create a new project by clicking **File**->**New**->**CCS Project**
3. Select **MSP430G2553** as the **Target**
4. Type in a name for the project
5. Select **Empty Project (with main.c)** from **Empty Projects**
6. Click **Finish**
7. Copy the following into the main file (modified from an example on TI's website: https://www.ti.com/tool/download/SLAC485)
```
#include <msp430.h>

//------------------------------------------------------------------------------
// Hardware-related definitions
//------------------------------------------------------------------------------
#define UART_TXD   0x02                     // TXD on P1.1 (Timer0_A.OUT0)

//------------------------------------------------------------------------------
// Conditions for 9600 Baud SW UART, SMCLK = 1MHz
//------------------------------------------------------------------------------
#define UART_TBIT_DIV_2     (1000000 / (9600 * 2))
#define UART_TBIT           (1000000 / 9600)

//------------------------------------------------------------------------------
// Global variables used for full-duplex UART communication
//------------------------------------------------------------------------------
unsigned int txData;                        // UART internal variable for TX

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------
void TimerA_UART_init(void);
void TimerA_UART_tx(unsigned char byte);
void TimerA_UART_print(char *string);

//------------------------------------------------------------------------------
// main()
//------------------------------------------------------------------------------
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
    {
      while(1);                               // do not load, trap CPU!!
    }

    DCOCTL = 0;                             // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                  // Set DCOCLK to 1MHz
    DCOCTL = CALDCO_1MHZ;

    P1OUT = 0x00;                           // Initialize all GPIO
    P1SEL = UART_TXD;                       // Timer function for TXD pins
    P1DIR = 0xFF;                           // Set all pins to output

    __enable_interrupt();

    TimerA_UART_init();                     // Start Timer_A UART
    TimerA_UART_print("Hello World \r\n");  // Print Hello World to UART
    while(1);
}

//------------------------------------------------------------------------------
// Function configures Timer_A for full-duplex UART operation
//------------------------------------------------------------------------------
void TimerA_UART_init(void)
{
    TACCTL0 = OUT;                          // Set TXD Idle as Mark = '1'
    TACCTL1 = SCS + CM1 + CAP + CCIE;       // Sync, Neg Edge, Capture, Int
    TACTL = TASSEL_2 + MC_2;                // SMCLK, start in continuous mode
}
//------------------------------------------------------------------------------
// Outputs one byte using the Timer_A UART
//------------------------------------------------------------------------------
void TimerA_UART_tx(unsigned char byte)
{
    while (TACCTL0 & CCIE);                 // Ensure last char got TX'd
    TACCR0 = TAR;                           // Current state of TA counter
    TACCR0 += UART_TBIT;                    // One bit time till first bit
    TACCTL0 = OUTMOD0 + CCIE;               // Set TXD on EQU0, Int
    txData = byte;                          // Load global variable
    txData |= 0x100;                        // Add mark stop bit to TXData
    txData <<= 1;                           // Add space start bit
}

//------------------------------------------------------------------------------
// Prints a string over using the Timer_A UART
//------------------------------------------------------------------------------
void TimerA_UART_print(char *string)
{
    while (*string) {
        TimerA_UART_tx(*string++);
    }
}
//------------------------------------------------------------------------------
// Timer_A UART - Transmit Interrupt Handler
//------------------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
#endif
{
    static unsigned char txBitCnt = 10;

    TACCR0 += UART_TBIT;                    // Add Offset to CCRx
    if (txBitCnt == 0) {                    // All bits TXed?
        TACCTL0 &= ~CCIE;                   // All bits TXed, disable interrupt
        txBitCnt = 10;                      // Re-load bit counter
    }
    else {
        if (txData & 0x01) {
          TACCTL0 &= ~OUTMOD2;              // TX Mark '1'
        }
        else {
          TACCTL0 |= OUTMOD2;               // TX Space '0'
        }
        txData >>= 1;
        txBitCnt--;
    }
}
```
8. Connect the board to the host using the provided USB cable
9. In the top left corner select the blue **Terminal** button
10. Choose **Serial Terminal** from the dropdown
11. Type in the COM port that the board is connect to (found in Device Manager)
12. Press OK
13. Press the button that looks like a Folder with curly braces to Flash the program.
14. After a few moments, "Hello World" should print to the Serial terminal.  Every time you press the reset button on the board, "Hello World" will print.
