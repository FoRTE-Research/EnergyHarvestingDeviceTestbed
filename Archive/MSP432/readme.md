1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP432P401R** as the **Target**
5. Type in a name for the project
6. Select **Empty Project (with main.c)** from **Project templates and examples**
7. Click **Finish**
8. Modify `main.c` so that it looks like the source code below:
```
#include "msp.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	P1OUT = 0x0;
	P1DIR = 0x1; // setup pin direction to output
	
	unsigned int x = 0;
	while(1) {
	    ++x;
	    if(x % 100000 == 0) {
	        x = 0;
	        P1OUT ^= 0x1; // toggle LED
	    }
	}
}
```
9. Connect the board to the host using the provided USB cable
10. Press the green bug tool symbol in the top toolbar to debug the program on the board
11. Press the button that looks like a play button to run the program (the LED should blink)

**(Optional) Blinking with RGB LED**\
P2 can be used to toggle the RGB LED instead of P1. The example code below changes the color of the LED between blinks. Modify `main.c` so that it looks like the source code below and run the program as previously specified.
```
#include "msp.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;    // stop watchdog timer

	P2->DIR |= 7;    // P2.2-2.0 set as output
	
	int blink = 1;
	volatile unsigned int x = 0;
	volatileint i = 0;

	while(1) {
	    ++x;
	    if (x % 100000 == 0) {
		if (blink == 1) {
		    P2->OUT = 1 <<(i % 3);    // change the color of the LED between red, green, and blue
		    ++i;
		    blink = 0;
		} else {
		    P2->OUT = 0;
		    blink = 1;
		}
	    }
	}
}
```
