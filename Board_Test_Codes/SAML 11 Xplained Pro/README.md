SAML 11 Xplained pro 

Setup:
======
1. Download and install the Atmel Studio v7.0.2389 from the microchip archives: https://www.microchip.com/en-us/tools-resources/archives/avr-sam-mcus . 
**Note:** Atmel Studio is changed to Microchip Studio. However, due to some issues with the IDE, the example codes don't compile and run properly with the latest Microchip Versions. Thus, all codes are tested on Atmel Studio v7.0.2389.

Running the USART_LED code:
==========================
1. Connect the SAML11 Xplained Pro board using USB. Go to File->Open->Project/Solution and select USART_LED.cproj. Build the solution. 
**Note:**It is important to import the same .cproj file instead of making a new file to incorporate the necessary configurations for LED blink and USART into the code. The main.c contains the USART and LED blink test code.
2. Go to **Debug**->**USART_LED Properties**. In the **Build** section, verify the configuration as "Release". In the **Device** section, verify that the current device to be ATSAML11E16A. In the **Tool** section, select the EDBG debugger/programmer detected when the board is connected. The interface should be SWD. Save the changes.
3. Go to Tools->Device Programming->Interface Settings. Select the EDBG Tool, ATSAML11E16A Device and SWD interface and click Apply. Click Read next to the Device Signature. 
4. Go to Tools->Device Programming->Memories. Click Program in the Flash section. Device is programmed if Erasing Device, Programming Flash and Verifying Flash are all OK. Close the terminal. 
6. LED0 should be on.
5. For the serial port go to Tools->Data Visualizer. EDBG Virtual COM Port should be automatically detected. Select the Baud Rate 115200, Parity None and Stop Bits as 1. Click Connect. A terminal should open up. Some values should be printed along with a string on the terminal. The LED should blink/ 




