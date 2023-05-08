#include <saml11e16a.h>
#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>

/* For measurement method; if TIMER is used then just set uncomment this line*/
#define TIMER

/* For HMAC */

#include "../hmac/hmac_sha256.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SHA256_HASH_SIZE 32

void start_timer_0_16_bit(void)
{
	GCLK->PCHCTRL[14].reg = (GCLK_PCHCTRL_CHEN|GCLK_PCHCTRL_GEN_GCLK0);
	TC0->COUNT16.CTRLA.bit.ENABLE = 0; // CNTLA is write protected to so we have to disable it before writing.
	while(TC0->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_ENABLE);
	TC0->COUNT16.CTRLA.bit.MODE = 0x1; // set the counter to be in 32 bit mode.
	TC0->COUNT16.DBGCTRL.bit.DBGRUN = 0x1; // keep timer running even when the device is halted.
	TC0->COUNT16.CTRLA.bit.ENABLE = 0x1; // start the counter
	while(TC0->COUNT16.SYNCBUSY.bit.ENABLE);
	
}


uint16_t read_time_0_16_bit(void)
{
	TC0->COUNT16.CTRLBSET.bit.CMD = 0X4;// READSYNC
	while(TC0->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_CTRLB);
	return TC0->COUNT16.COUNT.reg;
	
}


void start_timer_0_32_bit(void)
{
	/************************************************************************/
	/* 16 bit is not enough for most cases
	So this function makes it a 32 bit time.
	TC0 and TC1; TC1 is just a slave device.                                     */
	/************************************************************************/
	GCLK->PCHCTRL[14].reg = (GCLK_PCHCTRL_CHEN|GCLK_PCHCTRL_GEN_GCLK0);
	TC0->COUNT32.CTRLA.bit.ENABLE = 0; // CNTLA is write protected to so we have to disable it before writing.
	while(TC0->COUNT32.SYNCBUSY.reg & TC_SYNCBUSY_ENABLE);
	
	TC0->COUNT32.CTRLA.bit.MODE = 0x2; // set the counter to be in 32 bit mode.
	TC0->COUNT32.DBGCTRL.bit.DBGRUN = 0x1; // keep timer running even when the device is halted.
	TC0->COUNT32.CTRLA.bit.ENABLE = 0x1; // start the counter
	while(TC0->COUNT32.SYNCBUSY.bit.ENABLE);// wait for it to be activated
}

volatile uint32_t read_time_0_32_bit(void)
{ /**Dumps the timer cycles to a variable*/
	TC0->COUNT32.CTRLBSET.bit.CMD = 0X4;// READSYNC
	while(TC0->COUNT32.SYNCBUSY.reg & TC_SYNCBUSY_CTRLB);
	return TC0->COUNT32.COUNT.reg; // return count register.
}

int main(void)
{
	atmel_start_init();
	
	const char* str_data = "Hello World!";
	const char* str_key = "super-secret-key";
	uint8_t out[SHA256_HASH_SIZE];
	char out_str[SHA256_HASH_SIZE * 2 + 1];
	unsigned i;
	
	#ifdef TIMER
	volatile uint32_t a = 0;
	start_timer_0_32_bit();
	
	for(int test=0; test<1; test++){ // if you want average; increase the test variable range.
		// Call hmac-sha function
		hmac_sha256(str_key, strlen(str_key), str_data, strlen(str_data), &out, sizeof(out));
	}
	
	a = read_time_0_32_bit(); // add a watch point to this variable if you want to see it live.
	*(uint32_t *)(0x2000383C) = a; // store the timer data in the SRAM at @ 0x2000383C; plan is to get it out of the
	while(true);
	
	#else
	
	while (true) {
		// Call hmac-sha function
		hmac_sha256(str_key, strlen(str_key), str_data, strlen(str_data), &out, sizeof(out));
		gpio_toggle_pin_level(LED0); /*pulse the gpio everytime the execution of that function is done*/
	}

	// Convert `out` to string with printf
	//memset(&out_str, 0, sizeof(out_str));
	//for (i = 0; i < sizeof(out); i++) {
	//snprintf(&out_str[i*2], 3, "%02x", out[i]);
	//}

	//     Print out the result
	//printf("Message: %s\n", str_data);
	//printf("Key: %s\n", str_key);
	//printf("HMAC: %s\n", out_str);
	
	// This assertion fails if something went wrong
	//assert(strncmp(
	//out_str,
	//"4b393abced1c497f8048860ba1ede46a23f1ff5209b18e9c428bddfbb690aad8",
	//SHA256_HASH_SIZE * 2) == 0);
	
	#endif
}