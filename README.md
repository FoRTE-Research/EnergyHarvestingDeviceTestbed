# EnergyHarvestingDeviceTestbed

## MSP432

Install Texas Instruments Code Composer Studio: https://www.ti.com/tool/CCSTUDIO

## MSP430

Install Texas Instruments Code Composer Studio: https://www.ti.com/tool/CCSTUDIO

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
