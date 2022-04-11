## Getting started
Everything here is for Linux sytems, specifically Ubuntu 20.01. Download the following tools: 
- [J-link](https://www.segger.com/downloads/jlink/). Get the *.deb file for linux and execute ```sudo dpkg -i JLink_Linux_V764_x86_64```. The file name maybe something else depending on what version you are using. 
- Unzip the Downloaded [FreedomStdio](https://www.sifive.com/software). This the IDE we will use for the FE310 projects. 


FE310 Hardware setup
--------------------------------
Coonecting J-link:
- Follow j-link pin configuration and connect jumpers/wires to the [JTAG pins](https://github.com/mwelling/lofive/wiki#installing-lofive-enabled-freedom-e-sdk) of the FE310. 
![JLINK pins](J-Link_JTAG_Isolator_Pinout.png)
- JTAG Vref goes to  *+3.3Vout* line of the FE310 board
- RTCK does not need to connect to the board. It is *TCLK* that matters for now.
- Connect a power supply to the +5V line.
- The board does not have any LED or any power indicator. Let us connect an LED to GPI0-5/SPI1.SCK. 
- Connect the J-link to the computer and type ```JLinkExe -AutoConnect 1 -Device FE310 -If JTAG -Speed 4000 -jtagconf -1,-1```. this should connect the board to J-link. Type ```halt``` and it display the CPU status, e.g., register values. 
- Flashing light. The start.hex is a binary to blink LED (GPIO-5). If you have connected everything correctly, just execute ```source blink.sh``` from ./FE310 directory. Do you see blinking LED?
-----------------------------------------

FreedomStd
---------------------
1. Naviagte to the folder and run the executable in a shell ```./FreedomStudio```.  If you do not run this with root access you might get error beacuse it tries create a workspace in root directory. Just ignore those :warning: and choose a folder wherever you want.
2. FE310 directory has a Freedoom project---blinky---that should work righ out of the box. Just hit  'debug' (the bug looking icon like all other eclipes based IDE). If you hit reume button, the MCU should blink. 
 

FYI
-------------------
1. FreedomStd is not running the code
Launch the debugger from the project explorer window (left most window) and right click to find *Debug As* or *Run As*. For there go to *Debug configuration*  and click 

2. Erasing the full chip. Connect JLinkExe, Halt the CPU and execute ```exec EnableEraseAllFlashBanks``` then ```erase```. The entire Flash will be erased.
3. ```mem32 0x20000000, 10``` this command reads 10 words from the flash. Flash's base address is at  0x20000000. ```Wreg pc, 0x20000000``` point the PC to execute flash code. You can load binary image dynamically (```loadFile ./Executable_1.bin, 0x80000000``` in the SRAM.) 
4. This device has no internal Flash. but the board has 128Mbit QSPI.
5.  Power supply is interanlly routed from 5V header. so do nto worry about that.
6. 16MHz crystal in the board.
