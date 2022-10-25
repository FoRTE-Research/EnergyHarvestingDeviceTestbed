## Getting Started

### Installing

1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP430FR5994** as the **Target**
5. Type in a name for the project
6. Select **Empty Project (with main.c)** from **Project templates and examples**
7. Click **Finish**
8. Modify `main.c` so that it looks like the source code below:
```
#include "msp.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                                // to activate previously configured port settings
	P1OUT = 0x0;
	P1DIR = 0x7; // setup pin direction to output
	
	unsigned int x = 0;
	while(1) {
	    ++x;
	    if(x % 1000000 == 0) {
	        x = 0;
	        P1OUT ^= 0x7; // toggle LED
	    }
	}
}
```
9. Connect the board to the host using the provided USB cable
10. Press the green bug tool symbol in the top toolbar to debug the program on the board
11. Press the button that looks like a play button to run the program (the LED should blink)

### Compiler

* To use MSP430-GCC-OPENSOURCE — GCC - Open Source Compiler for MSP Microcontrollers, need to download it from [here](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE#downloads).
