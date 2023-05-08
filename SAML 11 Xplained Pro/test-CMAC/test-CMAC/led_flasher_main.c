#include <saml11e16a.h>
#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>

/* For measurement method; if TIMER is used then just set uncomment this line*/
#define TIMER

#include <string.h>

#include "cmac/cmac.h"
#include "cmac/utils.h"

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
	
	unsigned char key[] = {
		0x31, 0x50, 0x10, 0x47,
		0x17, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};

	unsigned char message[] = {
		"Information Security is a multidisciplinary area of study and professional activity which is concerned with the development and implementation of security mechanisms of all available types (technical, organizational, human-oriented and legal) to keep information in all its locations (within and outside the organization's perimeter) and, consequently, information systems, where information is created, processed, stored, transmitted and destroyed, free from threats. This project is finished by GUORUI XU."
	};

	unsigned char out[16];
	
	#ifdef TIMER
	
	volatile uint32_t a = 0;
	start_timer_0_32_bit();
	/* Test functions*/
	for(int test= 0; test<1; test ++){ // if you want average; increase the test variable range.
		aes_cmac(message, strlen((char*)message) + 1, (unsigned char*)out, key);
	}
	a = read_time_0_32_bit(); // add a watch point to this variable if you want to see it live.
	*(uint32_t *)(0x2000383C) = a; // store the timer data in the SRAM at @ 0x2000383C; plan is to get it out of the
	while(true);
	
	#else
	
	while (true) {
		aes_cmac(message, strlen((char*)message) + 1, (unsigned char*)out, key);
		gpio_toggle_pin_level(LED0); /*pulse the gpio everytime the execution of that function is done*/
	}

	//    printf("%sAES-128-CMAC Result%s\n", ACCENTCOLOR, DEFAULT);
	//    print_bytes(out, 16);
	#endif
}