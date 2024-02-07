
#include <stdio.h>      //include Serial Library
#include <time.h>       //include Time library
#include <metal/gpio.h> //include GPIO library, https://sifive.github.io/freedom-metal-docs/apiref/gpio.html
#include <metal/machine.h>
//#include <metal/spi.h>
#include <metal/init.h>

/** contexts **/

#include "test.h" // Change test.h to select different algorithms

#include <stdint.h>
#include <string.h>


#ifdef gladman_aes
#include "gladman/aestst.h"
#endif

#ifdef tiny_aes
#include "tiny_aes/aes.h"
#endif

#ifdef slow_tiny_aes
#include "aes.h"
#endif

#ifdef mbedtls_aes
#include "mbedtls/aes.h"
#endif

//typedef char uint8_t;

/** Globals (test inputs) **/
char key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73,
	0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07,
	0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14,
0xdf, 0xf4 };
char check_encrypt[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c,
0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#ifdef AES_CBC
uint8_t pt[MSG_LNGTH];
uint8_t ct[MSG_LNGTH];
// initialization vector for CBC mode
unsigned char iv[AES_BLOCK_SIZE_BYTES] = { 0xb2, 0x4b, 0xf2, 0xf7, 0x7a, 0xc5, 0xec, 0x0c, 0x5e,
0x1f, 0x4d, 0xc1, 0xae, 0x46, 0x5e, 0x75 };
#else
char pt[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d,
0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
char ct[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b,
0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#endif

/** contexts **/



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

// This increases precision
// Higher iteration counts produces better results

int AES_loop(void)
{ unsigned int i;
for(i =0; i<200; i++) // execution time should be 1/200
{	init_aes();
	test_encrypt();
	}
return 0;
	}

// Read 0x20010000
//char tx_buf[5] = {0x03, 0x20, 0x01, 0x00, 0x00};

// Read product ID
// Instruction is 0xAB, followed by 3 dummy bytes
// Then one byte to actually receive
//#define BUF_LEN 8
//volatile char tx_buf[8] = {0x9F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//volatile char rx_buf[8] = {0xDE, 0xAD, 0xBE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEF};
//
//#define BUF2_LEN 8
//volatile char tx2_buf[8] = {0x03, 0x01, 0x11, 0x24, 0x00, 0x00, 0x00, 0x00};
//volatile char rx2_buf[8] = {0xDE, 0xAD, 0xBE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEF};
//
//// Function to mess with QSPI Flash needs to execute out of RAM
//__attribute__ ((noinline, section(".data"), optimize("Os"))) void testFunc(void){
////void testFunc(void){
//  struct metal_spi *spi;
//  spi = metal_spi_get_device(0);
//  if(spi == NULL){
//    while(1);
//  }
//
//  struct metal_spi_config config = {
//    .protocol = METAL_SPI_SINGLE,
//    .polarity = 0,
//    .phase = 0,
//    .little_endian = 0,
//    .cs_active_high = 0,
//    .csid = 0,
//  };
//
//  // Init normal mode SPI to 100,000 baud
//  //metal_spi_init(spi, 100000);
//
//  //uintptr_t* QSPI_BASE = (uintptr_t*) 0x10014000;
//  uintptr_t* QSPI_FCTRL = (uintptr_t*) 0x10014060;
//
//  //// Take QSPI out of HW mode. This should crash the MCU
//  //// when this function returns
//  //*QSPI_FCTRL = 0;
//
//  //if(*QSPI_FCTRL == 1){
//  //  while(1);
//  //}
//
//  // 0x03 is normal read operation
//  // Read address 0x20020000 -> should be all 0xFF
//  //char tx_buf[5] = {0x03, 0x20, 0x02, 0x00, 0x00};
//
//  // Read address 0x20010000 -> should be some code
//  if(metal_spi_transfer(spi, &config, BUF2_LEN, tx2_buf, rx2_buf) != 0){ // This calls a vtable function defined for SPI0 that turns off XIP
//    while(1);
//  }
//  if(metal_spi_transfer(spi, &config, BUF_LEN, tx_buf, rx_buf) != 0){ // This calls a vtable function defined for SPI0 that turns off XIP
//    while(1);
//  }
//  __asm__("nop");
//  *QSPI_FCTRL = 1;
//  __asm__("nop");
//  volatile uint32_t i, r;
//  //for(i = 0; i < 1000; i++){
//  //  for(r = 0; r < 1000; r++){
//  //    *QSPI_FCTRL = 1;
//  //  }
//  //}
//  //while(1);
//}

// 16 blinks
#define AES_COUNT 256
#define COUNT_ADDR 0x80003FF0

// Default clock rate is 13.8 MHz
#define CYCLES_PER_SECOND 1380000

void metal_init_run(){
  // Replace weak init function with nothing; minimal boot
}

void metal_fini_run(){
  // Replace weak fini function with nothing; minimal boot
}

int main (void) {
  struct metal_gpio *led0;
  volatile uint32_t delay;

  led0 = metal_gpio_get_device(0);
  metal_gpio_disable_input(led0, 5);
  metal_gpio_enable_output(led0, 5);
  metal_gpio_disable_pinmux(led0, 5);

  // If blink count is an invalid number, it was corrupted. Reset
  if(*((uint16_t*) COUNT_ADDR) > AES_COUNT){
    *((uint16_t*) COUNT_ADDR) = 0;
  }

  init_aes();
  while(1){
    test_encrypt();
    if(*((uint16_t*) COUNT_ADDR) >= AES_COUNT){
      while(1){
        metal_gpio_set_pin(led0, 5, 1);
      }
    }
    // Light LED for 25 ms to show an encryption is done
    if(*((uint16_t*) COUNT_ADDR) % 16 == 0){
      metal_gpio_set_pin(led0, 5, 1);
      for(delay = CYCLES_PER_SECOND / 40; delay > 0; delay--);
      metal_gpio_set_pin(led0, 5, 0);
    }
    *((uint16_t*) COUNT_ADDR) += 1;
  }

  return 0;
}
