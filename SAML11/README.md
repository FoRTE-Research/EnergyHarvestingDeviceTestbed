


#### Software setup
- The development environment used in this experiment is [**Microchip studio**](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Downloads). There is no Linux version (at least not till now); so you will need windows for this.

- Use this IDE to open project *test_AES.atsln*. The [main.c](https://github.com/FoRTE-Research/EnergyHarvestingDeviceTestbed/blob/main/SAML11/test_AES_4MHZ/LEDflasher/main.c) file contains AES and timing measurement codes.

- Select Jlink as programming media in the project property setting. This option will not be available until the hardware is connected.

 
#### Hardware setup


- This project should run on both Xplained Pro and CW308T UFO ATSAML11 target board.

- Connect a jlink programmer to the J6 header in the UFO board. The board needs a separate power supply; so connect a 5V supply to J2. There are so many LDOs on the board so it could be a little confusing; so just set J1 (3.3Vcc) in a position such that the 3.3VCC indicator LED lights up.

  

#### Measuring execution time

- Build and load the binary from the project above.

- The LED in PA23 should start blinking. If you connect an Oscilloscope to this pin and you should see the line is toggling. Each pulse indicates the execution time of code in between lines (main.c) 277 and 278.


- To measure the time digitally uncomment line 8 ```#define TIMER```. Then, build and load the program; this will activate the internal timer and store the execution time in a variable. You can manually look at the cycle count using the microchip studio or if you have access to a Linux machine (with Jlink software setup), just run ```python3.8 get_time.py```. This will read (from the device) and calculate the execution time for the code in line 268.

Results:
- Default MCU freq (4 MHZ)
- Optimization level -o0

```markdown
| Method | Encryption | Decryption | Size (bytes) | Current |
|--------|------------|------------|--------------|---------|
| Scope  | 19.8ms     | 124.9ms    |         7884 | 0.4mA   |
| Timer  | 19.8ms     | 124.8ms    |              |         |