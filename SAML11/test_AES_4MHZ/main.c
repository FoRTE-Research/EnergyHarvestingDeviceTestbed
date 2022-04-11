
#include <saml11e16a.h>
#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>

/* For measurement method; if TIMER is used then just set uncomment this line/
//#define TIMER 



/*For aes*/


#include "test.h" // Change test.h to select different algorithms

#include <stdint.h>
#include <string.h>





#include "experiment_time.h"

#ifdef gladman_aes
#include "gladman/aestst.h"
#endif

#ifdef tiny_aes
#include "tiny_aes/aes.h"
#endif

#ifdef slow_tiny_aes
#include "slow_tiny_aes/aes.h"
#endif

#ifdef mbedtls_aes
#include "mbedtls/aes.h"
#endif


/** Globals (test inputs) **/
uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73,
	0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07,
	0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14,
0xdf, 0xf4 };
uint8_t check_encrypt[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c,
0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#ifdef AES_CBC
uint8_t pt[MSG_LNGTH];
uint8_t ct[MSG_LNGTH];
// initialization vector for CBC mode
unsigned char iv[AES_BLOCK_SIZE_BYTES] = { 0xb2, 0x4b, 0xf2, 0xf7, 0x7a, 0xc5, 0xec, 0x0c, 0x5e,
0x1f, 0x4d, 0xc1, 0xae, 0x46, 0x5e, 0x75 };
#else
uint8_t pt[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d,
0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
uint8_t ct[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b,
0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#endif

/** contexts **/
#ifdef tiny_aes
struct AES_ctx ctx;
#endif
#ifdef mbedtls_aes
struct mbedtls_aes_context ctx;
#endif

/** define keysizes **/
#if defined AES_128
long keysize = 128;
#elif defined AES_192
long keysize = 192;
#else
long keysize = 256;
#endif

/** Call initialization functions for different AES implementations **/
void init_aes()
{
	#ifdef gladman_aes
	gladman_init(key, pt, ct, keysize);
	#endif
	#ifdef tiny_aes
	AES_init_ctx(&ctx, key);
	#endif
	#ifdef mbedtls_aes
	mbedtls_aes_init(&ctx);
	mbedtls_aes_setkey_enc(&ctx, key, keysize);
	#endif
}

void test_encrypt()
{
	/** Gladman AES **/
	#ifdef gladman_aes
	#ifdef AES_128
	aes_gladman_128_encrypt(key, pt, ct);
	#elif AES_192
	aes_gladman_192_encrypt(key, pt, ct);
	#else // AES_256
	aes_gladman_256_encrypt(key, pt, ct);
	#endif
	#endif

	/** tiny AES **/
	#ifdef tiny_aes
	AES_encrypt(&ctx, key, pt, ct);
	#endif

	/** SLOW tiny AES **/
	#ifdef slow_tiny_aes
	test_AES_encrypt();
	#endif

	/** MbedTLS AES **/
	#ifdef mbedtls_aes
	mbedtls_internal_aes_encrypt(&ctx, pt, ct);
	#endif
}

void test_decrypt()
{
	/** Gladman AES **/
	#ifdef gladman_aes
	#ifdef AES_128
	aes_gladman_128_decrypt(key, ct, pt);
	#elif AES_192
	aes_gladman_192_decrypt(key, ct, pt);
	#else // AES_256
	aes_gladman_256_decrypt(key, ct, pt);
	#endif
	#endif

	/** tiny AES **/
	#ifdef tiny_aes
	AES_decrypt(&ctx, key, ct, pt);
	#endif

	/** SLOW tiny AES **/
	#ifdef slow_tiny_aes
	test_AES_decrypt();
	#endif

	/** MbedTLS AES **/
	#ifdef mbedtls_aes
	mbedtls_internal_aes_decrypt(&ctx, pt, ct);
	#endif
}

int check_result()
{
	return memcmp((char*) pt, (char*) check_encrypt, 16);
}

#ifdef AES_CBC
void aes_encrypt_cbc(size_t length) {
	uint8_t * p = pt;
	uint8_t * c = ct;

	while (length > 0) {
		// Perform IV xor PT for 128 bits
		int i = 0;
		for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
		p[i] = p[i] ^ iv[i];

		// Perform 1 encrypt
		test_encrypt();

		// IV is now CT
		memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

		// Go to next block of PT
		p += AES_BLOCK_SIZE_BYTES;
		c += AES_BLOCK_SIZE_BYTES;
		length -= AES_BLOCK_SIZE_BYTES;
	}
}

void aes_decrypt_cbc(size_t length) {
	uint8_t * p = pt;
	uint8_t * c = ct;

	while (length > 0) {
		// Perform 1 encrypt
		test_decrypt();

		// Perform IV xor PT for 128 bits
		int i = 0;
		for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
		p[i] = p[i] ^ iv[i];

		// IV is now CT
		memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

		// Go to next block of PT
		p += AES_BLOCK_SIZE_BYTES;
		c += AES_BLOCK_SIZE_BYTES;
		length -= AES_BLOCK_SIZE_BYTES;
	}
}
#endif



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
	
	#ifdef TIMER
			volatile uint32_t a = 0; 
			start_timer_0_32_bit();
			/* Test functions*/
			init_aes();
			for(int test= 0; test<1; test ++){ // if you want average; increase the test variable range.
			test_encrypt(); // replace with test_decrypt to test the drcypt execution
			}
			a = read_time_0_32_bit(); // add a watch point to this variable if you want to see it live.
			*(uint32_t *)(0x2000383C) = a; // store the timer data in the SRAM at @ 0x2000383C; plan is to get it out of the
			while(true);
	
	#else
	
	while (true) {
		init_aes();
		test_encrypt();
		//test_decrypt();
		gpio_toggle_pin_level(LED0); /*pulse the gpio everytime the execution of that function is done*/
	}

	#endif
	

	
	
	
	







}
