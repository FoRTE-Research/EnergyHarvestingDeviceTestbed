## Adafruit METRO M0 Express
1. Install [Arduino IDE](https://www.arduino.cc/en/software) 
2. [Set up board](https://learn.adafruit.com/adafruit-metro-m0-express/using-with-arduino-ide)
3. Open the AdfruitMetroM0ExpressBlink.ino file in Arduino IDE.
5. Run the code and get the execution time from the [serial monitor](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor) in Arduino IDE

- Resons for using Arduino IDE
  - Arduino CLI does not support Serial as of now (May 11 2022)
  - Arduino extension for VS Code has glitches when running Serial (May 11 2022)

- Arduino IDE does not recognize .inc files. To solve this problem, include the absolute path for the .inc file.

- On the optimize menu for Adafruit METRO M0 Express, there isn't an option for -O0. In order to add the option for no optimization, find the boards.txt file and add these two lines:

  ```
  adafruit_metro_m0.menu.opt.no=No (-O0) (no optimization)      
  adafruit_metro_m0.menu.opt.no.build.flags.optimize=-O0
  ```

  above 

  ```
  adafruit_metro_m0.menu.opt.small=Small (-Os) (standard)       
  adafruit_metro_m0.menu.opt.small.build.flags.optimize=-Os
  ```

  This will add an option for no optimization on the menu.