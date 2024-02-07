1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP430FR5994** as the **Target**
5. Type in a name for the project
6. Select **Empty Project (with main.c)** from **Project templates and examples**
7. Click **Finish**
8. Copy the test code in the `main.c`.

**Note : UART code uses the MSP430 driverlib library which is included in the MSP430WARE which can be downloaded from here: https://www.ti.com/tool/MSPWARE. For ease of operation, the code workspace can be set up in the examples folder inside the msp\MSP430Ware_3_80_14_01\driverlib\examples\MSP430FR5xx_6xx folder. 

9. Copy the driverlib folder inside your project folder in the workspace. The driverlib folder is located somewhere on your system like: C:\ti\msp\MSP430Ware_3_80_14_01\driverlib\driverlib
10. We need to include the driverlib path in the build settings of our project. Make sure your current project is the active project in the project explorer. In CCS studio to **Project**->**Show build settings**->**Build**->**MSP430 Compiler**->**Include Options**. Click on the Add.. button and add the path of the driverlib, driverlib\MSP430FR5xx_6xx and driverlib\MSP430FR5xx_6xx\inc folders inside your project. 
The added path should look something like this: 
C:\ti\msp\MSP430Ware_3_80_14_01\driverlib\examples\MSP430FR5xx_6xx\workspace_v12_MSP430FR5994\MSP430FR5994_UART\driverlib
C:\ti\msp\MSP430Ware_3_80_14_01\driverlib\examples\MSP430FR5xx_6xx\workspace_v12_MSP430FR5994\MSP430FR5994_UART\driverlib\MSP430FR5xx_6xx
C:\ti\msp\MSP430Ware_3_80_14_01\driverlib\examples\MSP430FR5xx_6xx\workspace_v12_MSP430FR5994\MSP430FR5994_UART\driverlib\MSP430FR5xx_6xx\inc
11. The given code tests LED blinking and UART functionality on the board. To test the LED blinking code independently, comment the **#define UART_LED** in the code. To test the UART with LED blinking, uncomment the **#define UART_LED** in the code. 
12. Connect the board to the host using the provided USB cable.
13. Press the green bug tool symbol in the top toolbar to debug the program on the board.
14. Press the button that looks like a play button to run the program.
15. For the LED code, LED1 and LED2 should blink.(If it is not blinking, check if the LED jumpers are connected on the board).
16. For the UART+LED code, LED1 should blink. In CCS, go to **View**->**Terminal**->**Choose Terminal: Serial Terminal**. In the terminal window, click on the monitor icon to open and configure a new terminal for UART. Select the correct COM Serial port, Baud rate= 9600, Data size=8, Parity=None, Stop bits=1 and press ok. The terminal should print some values and the LED should blink.

**Note: Check the code for correct UART terminal settings. For the MSP boards, 2 COM ports will be visible in the in the Ports section of the device manager. Select the port saying "UART".  

