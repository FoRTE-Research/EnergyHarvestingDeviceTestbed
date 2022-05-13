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
	    if(x % 1000000 == 0) {
	        x = 0;
	        P1OUT ^= 0x1; // toggle LED
	    }
	}
}
```
9. Connect the board to the host using the provided USB cable
10. Press the green bug tool symbol in the top toolbar to debug the program on the board
11. Press the button that looks like a play button to run the program (the LED should blink)
