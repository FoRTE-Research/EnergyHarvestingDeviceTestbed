Setup:
=====
 1. Download and install the Keil uVision and the corresponding Software packs for Ambiq Micro AMA3B1KK-KBR by    following the given link:  https://developer.arm.com/documentation/101407/0538/About-uVision/Installation
 2. Download and extract the Ambiq Suite SDK to your preferred location https://github.com/sparkfun/AmbiqSuiteSDK
 3. Download and install the latest JLink tools : https://www.segger.com/downloads/jlink/ . Tools of interest are J-Flash Lite and J-Link SWO Viewer.

Running default Binary Counter Example: 
=======================================
 1. Go to the Ambiq Suite SDK directory. In that directory go to : \boards\apollo3_evb\examples\binary_counter
 2. In the binary_counter folder, go inside the Keil folder and open binary_counter.uvprojx with Keil uVision.
 3. Flash this project into the Apollo3 board and press the reset button. 5 LEDs on the evaluation board should run a binary counter sequence.

Running the hello_world_uart:
=============================
 1. Place the hello_world_uart folder inside the AmbiqSuiteSDK directory in the \boards\apollo3_evb\examples folder and follow the Binary counter example steps to flash the code. 
 2. Configure PuTTY or Tera Term for UART at 115200 baud. 

Name:
=====
 hello_world_uart


Description:
============
 A simple "Hello World" example using the UART peripheral.


This example prints a "Hello World" message with some device info
over UART at 115200 baud.
To see the output of this program, run a terminal appl such as
Tera Term or PuTTY, and configure the console for UART.
The example sleeps after it is done printing.


******************************************************************************