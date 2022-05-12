# EnergyHarvestingDeviceTestbed

|Device|ISA|Default Clock (MHz)|SRAM (KB)|NVM (KB)|Dev. Enivronment|DMIPS/MHz|Coremark/MHz|
|---|---|---|---|---|---|---|---|
|[MSP430G2553IN20](https://www.digikey.com/en/products/detail/texas-instruments/MSP-EXP430G2ET/9608004?s=N4IgTCBcDaILYGcAOAWAzABgAQHMwFMAXEAXQF8g)|MSP430 (Flash)|1|0.5|16|Great| |1.11|
|[MSP430FR5994](https://www.ti.com/tool/MSP-EXP430FR5994?utm_source=google&utm_medium=cpc&utm_campaign=epd-msp-430-prodfolderdynamic-cpc-pf-google-wwe&utm_content=prodfolddynamic&ds_k=DYNAMIC+SEARCH+ADS&DCM=yes&gclid=Cj0KCQjwvO2IBhCzARIsALw3ASqUf7gxsO9rVTdfKJMEaIDoS4b-fNDCS6sCe2KYl0S6dPbcUmKdx_waAjakEALw_wcB&gclsrc=aw.ds)|MSP430X (FRAM)|1|8|256|Great| |1.11|
|[Adafruit METRO M0 (ATSAMD21G18)](https://www.adafruit.com/product/3505)|ARM Cortex-m0+ (v6m)|48|32|256|Bad|0.95|2.46|
|[MSP432](https://www.ti.com/tool/MSP-EXP432P401R?utm_source=google&utm_medium=cpc&utm_campaign=epd-null-null-OPN_EN-cpc-evm-google-wwe&utm_content=Device_ToolFolder&ds_k=MSP-EXP432P401R&DCM=yes&gclid=Cj0KCQjwvO2IBhCzARIsALw3ASpg2iltfqWzDLmrjK7SnvtKGD9A2jZRPM57xBkQBrc4LCYNG_xSahUaAihEEALw_wcB&gclsrc=aw.ds)|ARM Cortex-m4F (v7m)|3|64|256|Great|1.27|3.42|
|[Apollo 3 Blue](https://www.digikey.com/en/products/detail/sparkfun-electronics/DEV-15170/9962475?s=N4IgjCBcoLQBxVAYygMwIYBsDOBTANCAPZQDa4ArAGwIC6AvvYQExkgAiAogGoxgVgA7AAYQDIA)|ARM Cortex-m4F (v7m) (subthreshold)|48|384|1024|Bad|1.27|3.42|
|[SAML11 UFO Target](https://www.mouser.com/datasheet/2/894/NAE-CW308T-ATSAML11_datasheet-1601385.pdf)|ARM Cortex-m23 (v8m)|32|16|64|Good|0.98|2.64|
|[LoFive R1](https://store.groupgets.com/products/lofive-risc-v)|RV32IMAC|16|16|16384|Good|1.61|2.73|

## MSP432

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

## MSP430G2553

1. Download and install [Texas Instruments Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
2. Start CCS
3. Create a new project by clicking **File**->**New**->**CCS Project**
4. Select **MSP430G2553** as the **Target**
5. Type in a name for the project
6. Select **Empty Project (with main.c)** from **Project templates and examples**
7. Click **Finish**
8. Modify `main.c` so that it looks like the source code below:
```
#include "msp.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
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

## MSP430FR5994

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

## Apollo3 Blue
Aside from the actual Sparkfun Edge development board (https://www.sparkfun.com/products/15170), you need a CH340C serial to USB adapter (https://www.sparkfun.com/products/15096).

## Adafruit METRO M0 Express
1. Install [Arduino IDE](https://www.arduino.cc/en/software) 
2. [Set up board](https://learn.adafruit.com/adafruit-metro-m0-express/using-with-arduino-ide)
3. Change the name of the file containing the main function to be the same with the directory and change the extension to (ex: If the name of the directory is test, and the main file is main.c, then change the file name from main.c to test.ino)
4. Change the name of the main function to void loop()
5. Run the code and get the execution time from the [serial monitor](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor) in Arduino IDE

Resons for using Arduino IDE
- Arduino CLI does not support Serial as of now (May 11 2022)
- Arduino extension for VS Code has glitches when running Serial (May 11 2022)

### Running AES
First, download the Ambiq Suite SDK for developing on Sparkfun Ambiq boards.
```
git clone --recursive https://github.com/sparkfun/AmbiqSuiteSDK
```

Next download and apply the serial adapter driver update.
```
git clone https://github.com/juliagoda/CH341SER.git
cd CH341SER
make
sudo make load
```

Next, navigate to the project directory for AES on the Apollo board:
```
cd aes/apollo/gcc
```

You are now ready to flash the AES program to the Apollo board.
Connect the serial-to-usb adapter to the PC and the Apollo board to the adapter.
Note that **you must run the make command as sudo** (because this command is going to flash the board) and **you must press down button 14 on the Edge board during programming** (to use the bootloader).
The format of the make command will vary depending on your installation. Generally:
```
sudo make BOARDPATH=<Ambiq SDK Location>/boards_sfe/edge COM_PORT=<The USB port the adapter is connected to> ASB_UPLOAD_BAUD=921600 SDKPATH=<Ambiq SDK Location> COMMONPATH=<Ambiq SDK Location>/boards_sfe/common bootload_asb
```
As an example, my complete make command is:
```
sudo make BOARDPATH=/home/harrison/AmbiqSuiteSDK/boards_sfe/edge COM_PORT=/dev/ttyUSB0 ASB_UPLOAD_BAUD=921600 SDKPATH=/home/harrison/AmbiqSuiteSDK COMMONPATH=/home/harrison/AmbiqSuiteSDK/boards_sfe/common bootload_asb
```

After programming, press the RST button on the Edge board. The green LED (labelled 44 on the silkscreen) should light up, indicating that the AES encryption succesfully completed.

### Measuring execution time
The provided test code includes two ways to measure AES execution time.
The primary way is through an on-chip 3MHz hardware timer, the result of which is output over UART.
Alternatively, the code also toggles GPIOs to be measured by an oscilloscope for timing the AES execution.

#### Timer
Connect the device to a UART terminal with 115200 baud rate, 8 data bits, no parity, and 1 stop bit.
Reset the device to re-execute the AES execution.
The device will output the execution time in micro-seconds over UART.

#### Oscilloscope
Probe pin 1 (labelled on the silkscreen) and reset the device to re-execute the AES execution.
Before AES encryption, the pin is cleared.
Then, the pin is set immediately before the AES encryption and cleared immediately after.
Below is an example of the expected waveform for AES192.
![AES192 Encryption Waveform](aes192apollo.png)
