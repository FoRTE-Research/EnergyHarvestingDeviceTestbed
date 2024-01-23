1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP430G2553** as the **Target**
5. Type in a name for the project
6. Select **Blink The LED** from **Basic Examples**
7. Click **Finish**
8. Modify `main.c` so that it looks like the source code below:
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
