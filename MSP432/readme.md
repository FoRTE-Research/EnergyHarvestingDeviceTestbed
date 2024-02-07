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

**LED + UART test code using Driverlib**

1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. To download the GCC ARM compiler, Go to **Help**->**Install GCC ARM Compiler Tools ...**. Under Name tab check the **ARM GCC Tools** and click **Next** till the installation is complete.
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP432P401R** as the **Target** and **GNU vx.x.x(Linaro)** as the Compiler version. 
5. Type in a name for the project
6. Select **Empty Project (with main.c)** from **Project templates and examples**
7. Click **Finish**
8. Copy the test code in the `main.c`.
9. In CCS studio go to **Project**->**Show build settings**->**Build**->**GNU Compiler**->**Runtime** and set **Use floating point hardware(-m-float-abi)** to **softfp** instead of **hard**. (This is to resolve any -VFP errors in the future)

**Note : UART code uses the MSP432 driverlib library which can be downloaded here: https://www.ti.com/tool/MSPDRIVERLIB. For ease of operation, the code workspace can be set up in the examples folder inside the driverlib directory. 

9. Copy the driverlib folder inside your project folder in the workspace. The folder is located somewhere on your system like: C:\ti\msp432_driverlib_3_21_00_05\driverlib
10. We need to include the driverlib path in the build settings of our project. Make sure your current project is the active project in the project explorer. In CCS studio go to **Project**->**Show build settings**->**Build**->**GNU Compiler**->**Directories**. Click on the Add.. button and add the path of the driverlib, driverlib\MSP432P4XX and driverlib\MSP432P4XX\gcc folders inside your project. 
The added path should look something like this: 
C:\ti\msp432_driverlib_3_21_00_05\examples\MSP432P4xx\workspacev12_MSP432\MSP432_RSA_UART_GNU\driverlib\MSP432P4xx\gcc
C:\ti\msp432_driverlib_3_21_00_05\examples\MSP432P4xx\workspacev12_MSP432\UART_LED_MSP432\driverlib\MSP432P4xx
C:\ti\msp432_driverlib_3_21_00_05\examples\MSP432P4xx\workspacev12_MSP432\UART_LED_MSP432\driverlib 
11. The given code tests LED blinking and UART functionality on the board. To test the LED blinking code independently, comment the **#define UART_LED** in the code. To test the UART with LED blinking, uncomment the **#define UART_LED** in the code. 
12. Connect the board to the host using the provided USB cable.
13. Press the green bug tool symbol in the top toolbar to debug the program on the board.
14. Press the button that looks like a play button to run the program.
15. For the LED code, LED1 should blink.(If it is not blinking, check if the LED1 jumpers are connected on the board).
16. For the UART+LED code, LED1 should blink. In CCS, go to **View**->**Terminal**->**Choose Terminal: Serial Terminal**. In the terminal window, click on the monitor icon to open and configure a new terminal for UART. Select the correct COM Serial port, Baud rate= 9600, Data size=8, Parity=None, Stop bits=1 and press ok. The terminal should print some values and the LED should blink.

**Note: Check the code for correct UART terminal settings. For the MSP boards, 2 COM ports will be visible in the in the Ports section of the device manager. Select the port saying "UART".  


