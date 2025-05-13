# Energy Harvesting Device Testbed

This repository contains the codes for an emmbedded device 'Hello World' that blinks the LED our communicates via UART. We support the following targets:

|Device|ISA|Default Clock (MHz)|SRAM (KB)|NVM (KB)|Dev. Enivronment|DMIPS/MHz|Coremark/MHz|
|---|---|---|---|---|---|---|---|
|[MSP430G2553IN20](https://www.digikey.com/en/products/detail/texas-instruments/MSP-EXP430G2ET/9608004?s=N4IgTCBcDaILYGcAOAWAzABgAQHMwFMAXEAXQF8g)|MSP430 (Flash)|1|0.5|16|Great| |1.11|
|[MSP430FR5994](https://www.ti.com/tool/MSP-EXP430FR5994?utm_source=google&utm_medium=cpc&utm_campaign=epd-msp-430-prodfolderdynamic-cpc-pf-google-wwe&utm_content=prodfolddynamic&ds_k=DYNAMIC+SEARCH+ADS&DCM=yes&gclid=Cj0KCQjwvO2IBhCzARIsALw3ASqUf7gxsO9rVTdfKJMEaIDoS4b-fNDCS6sCe2KYl0S6dPbcUmKdx_waAjakEALw_wcB&gclsrc=aw.ds)|MSP430X (FRAM)|1|8|256|Great| |1.11|
|[Adafruit METRO M0 (ATSAMD21G18)](https://www.adafruit.com/product/3505)|ARM Cortex-m0+ (v6m)|48|32|256|Bad|0.95|2.46|
|[MSP432](https://www.ti.com/tool/MSP-EXP432P401R?utm_source=google&utm_medium=cpc&utm_campaign=epd-null-null-OPN_EN-cpc-evm-google-wwe&utm_content=Device_ToolFolder&ds_k=MSP-EXP432P401R&DCM=yes&gclid=Cj0KCQjwvO2IBhCzARIsALw3ASpg2iltfqWzDLmrjK7SnvtKGD9A2jZRPM57xBkQBrc4LCYNG_xSahUaAihEEALw_wcB&gclsrc=aw.ds)|ARM Cortex-m4F (v7m)|3|64|256|Great|1.27|3.42|
|[Apollo 3 Blue](https://www.digikey.com/en/products/detail/sparkfun-electronics/DEV-15170/9962475?s=N4IgjCBcoLQBxVAYygMwIYBsDOBTANCAPZQDa4ArAGwIC6AvvYQExkgAiAogGoxgVgA7AAYQDIA)|ARM Cortex-m4F (v7m) (subthreshold)|48|384|1024|Bad|1.27|3.42|
|[SAML11 UFO Target](https://www.mouser.com/datasheet/2/894/NAE-CW308T-ATSAML11_datasheet-1601385.pdf)|ARM Cortex-m23 (v8m)|32|16|64|Good|0.98|2.64|
|[SAML11 Xplained Pro](https://www.microchip.com/en-us/development-tool/dm320205)|ARM Cortex-m23 (v8m)|32|16|64|Good|0.98|2.64|
|[LoFive R1](https://store.groupgets.com/products/lofive-risc-v)|RV32IMAC|16|16|16384|Good|1.61|2.73|
|[Hifive 1 Rev B](https://store.groupgets.com/products/lofive-risc-v](https://www.sifive.com/boards/hifive1-rev-b)|RV32IMAC|320|16|32,000|Good|1.61|2.73|

To test the blinky LED-based 'Hello World', comment the "UART_LED" macro at the top of the code.
To test the both the LED- and UART-based 'Hello World', uncomment the "UART_LED" macro at the top of every code.
Detailed instructions to setup and test the boards are included in the target-dedicated folders.
