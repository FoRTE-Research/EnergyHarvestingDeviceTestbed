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

## Adafruit METRO M0 Express
1. Install [Arduino IDE](https://www.arduino.cc/en/software) 
2. [Set up board](https://learn.adafruit.com/adafruit-metro-m0-express/using-with-arduino-ide)
3. Change the name of the file containing the main function to be the same with the directory and change the extension to (ex: If the name of the directory is test, and the main file is main.c, then change the file name from main.c to test.ino)
4. Change the name of the main function to void loop()
5. Run the code and get the execution time from the [serial monitor](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor) in Arduino IDE

Resons for using Arduino IDE
- Arduino CLI does not support Serial as of now (May 11 2022)
- Arduino extension for VS Code has glitches when running Serial (May 11 2022)

Arduino IDE does not recognize .inc files. To solve this problem, include the absolute path for the .inc file.

- On the optimize menu for Adafruit METRO M0 Express, there isn't an option for -O0. In order to add the option for no optimization, find the boards.txt file and add these two lines:

`adafruit_metro_m0.menu.opt.no=No (-O0) (no optimization)`      
`adafruit_metro_m0.menu.opt.no.build.flags.optimize=-O0`

above 

`adafruit_metro_m0.menu.opt.small=Small (-Os) (standard)`       
`adafruit_metro_m0.menu.opt.small.build.flags.optimize=-Os`

This will add an option for no optimization on the menu.

### Baremetal
Getting truly bare-metal access to the SAMD21 chip on this board is a fairly involved process because Adafruit ships it with a locked-down bootloader so that you can use the Arduino IDE, CircuitPython, etc. These instructions are for if you'd rather develop using "normal C".

You need a J-Link debug probe and the J-Link software; we use the [J-Link EDU Mini](https://www.segger.com/products/debug-probes/j-link/models/j-link-edu-mini/).
You also need the [ARM development toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads).
Installing the J-Link software and ARM toolchain is left as an exercise for the reader.

#### Erasing the Adafruit bootloader
1. Connect the JLink probe to the Metro M0 Express board through the 10-pin connector, and power the board through the micro-usb or barrel connector.
2. Open the JLink GDB server to debug the SAMD21 chip: `JLinkGDBServer -if swd -device ATSAMD21G18A`. It should start waiting for a GDB connection; one of the output lines will be `Listening on TCP/IP port <portNumber>`. Note this port number.
3. In another terminal, open the ARM debugger: `arm-none-eabi-gdb`. Connect to the SAMD21 through the JLink GDB server: `target remote localhost:<portNumber>`.
4. The SAMD21 NVM controller locks down the first segment of Flash so that you cannot tamper with the bootloader; if you try to erase the Flash (and, by extension, program the Flash with new firmware), it will fail. We need to disable the Flash bootloader protection in the NVM controller.
5. The bootloader protection bits are at location 0x00804000. Read these bits out: `monitor MemU8 0x804000`. GDB should return the data at this byte; in my case, it was 0x72. Bits 2:0 of this field indicate the protected boot loader size: 0x72 indicates an 8192-byte write-protected bootloader (see the SAMD21 family datasheet Table 22.6.5).
6. Modify the protection bits: I'd rather not touch the other NVM control bits so I just set bits 2:0 to 0x7, indicating a bootloader size of 0 (no write protection): `monitor WriteU8 0x804000 0x77`.
7. Changes to these bits take effect on device reset: `monitor reset`.

You only have to do the above procedure once. At this point, the SAMD21 is programmable through JLink/GDB like any other target: repeat steps 1-3 to connect to the chip, `file <filename>` the executable you wish to program, and `load` it to the board.

#### Default NVM user row configuration
In case you somehow delete the NVM user row like I often do, the default (and most useful; WDT disabled, no bootloader/EEPROM) user row configuration is `D8E0C777 FFFF005A`.

## Apollo3 Blue
Aside from the actual Sparkfun Edge development board (https://www.sparkfun.com/products/15170), you need a CH340C serial to USB adapter (https://www.sparkfun.com/products/15096).

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
