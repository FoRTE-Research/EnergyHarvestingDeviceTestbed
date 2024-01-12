Setup HiFive1-revb:
===================

1. Download and install the Freedom studio from the SiFive website : https://www.sifive.com/boards/hifive1-rev-b
2. Connect the board to the host using the usb cable. Start FreedomStudio. Go to File->New->Freedom E SDK Project. 
3. Select Target as sifive-hifive1-revb. Select Next and set the Project name. Click on Finish. 
4. Edit Configuration and launch dialog box will open up. Press Debug. (If the dialog box doesn't appear, go to Run->Debug)
5. Go to Terminal. Select the COM port and Baud as 115200(default).
6. Press the "Play" button to start the debugger. Output can be seen on the terminal.

Setup Debug Configurations:
===========================

Verify whether the debug configurations are as below if the code isn't running. 
1. Build the project by selecting the "Release" configuration under the Build icon instead of "Debug".
2. Go to **Run**->**Debug Configurations**->**SiFive GDB SEGGER J-Link Debugging**. Create a new configuration if there isn't one already by clicking on the "New launch configuration" icon and Name the configuration. 
3. In the **Main** section, in the C/C++Application, give the path of the src/debug/*project_name*.elf. Build Configuration should be set to "Select Automatically". Click on Apply.
4. In the **Target** section, the DTS File path should be *project_folder*\bsp\design.dts. Put the absoulte path of the design.dts file if necessary. The Selected cpu should be cpu@0. Click on Apply.
5.  In the **Debugger** section, the Device name should be FE310. Click Apply.
6.  In the **Startup** section, check if the Load Symbols and Load executable is selected, and the "Use project binary" points to the debug/*project_name*.elf. Press Debug to flash the code.
To use the same configuration again, Build using the "Release" configuration under the Hammer icon. Press on the "Debug as" tool drop down menu to select the recently created configuration. 