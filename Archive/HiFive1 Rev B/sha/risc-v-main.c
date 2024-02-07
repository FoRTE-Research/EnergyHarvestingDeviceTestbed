#include <stdio.h>      //include Serial Library
#include <stdint.h>
#include <string.h>
#include <metal/cpu.h>
#include <metal/interrupt.h>
#include <metal/timer.h>
#include <metal/gpio.h> //include GPIO library, https://sifive.github.io/freedom-metal-docs/apiref/gpio.html
#include </Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/bsp/install/include/metal/machine.h>
#include <metal/clock.h>
#include <metal/spi.h>
#include <metal/init.h>
#include <limits.h>
#include <metal/machine/platform.h>

/** need to choose which SHA implementation to run **/
#define gladman_sha
//#define saddi_sha
//#define mbedtls_sha

#ifdef gladman_sha
//#include <memory.h>
#include <ctype.h>
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/gladman/sha2.h"
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/gladman/sha2.c"
#endif
#ifdef saddi_sha
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/saddi/sha256.h"
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/saddi/sha256.c"
#include <stdlib.h>
#endif
#ifdef mbedtls_sha
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/mbedtls/sha256.h"
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/sha/mbedtls/sha256.c"
#endif

#define DIGEST_BYTES (256/8)

/** Globals (test inputs) **/
unsigned char data[] = "abc"; // Data you want to hash
unsigned char check_sha256[] = { 220, 17, 20, 205, 7, 73, 20, 189, 135, 44, 193,
		249, 162, 62, 201, 16, 234, 34, 3, 188, 121, 119, 154, 178, 225, 125,
		162, 87, 130, 166, 36, 252 }; // Used to verify the hash function
uint8_t hash[DIGEST_BYTES]; // the output of SHA256 will be stored here
size_t len = sizeof(data);

/** contexts **/
#ifdef gladman_sha
sha256_ctx cx[1];
#endif
#ifdef saddi_sha
SHA256_CTX ctx;
#endif
#ifdef mbedtls_sha
mbedtls_sha256_context ctx;
#endif

/** Call initialization functions for different SHA implementations **/
void init_sha() {
#ifdef gladman_sha
    sha256_begin(cx);
#endif
#ifdef saddi_sha
    sha256_init(&ctx);
#endif
#ifdef mbedtls_sha
    mbedtls_sha256_init(&ctx);
#endif
}

void test_sha256() {
#ifdef gladman_sha
    sha256(hash, data, len, cx);
#endif
#ifdef saddi_sha
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, hash);
#endif
#ifdef mbedtls_sha
	mbedtls_sha256(data, len, hash, 0, ctx);
#endif
// hash now contains the output of SHA-256
}

//int check_result()
//{
//    return memcmp((uint8_t*) hash, (uint8_t*) check_sha256, DIGEST_BYTES);
//}

double cycles_to_ms(unsigned long long cycles) {
	double frequency = 32000000.0; // HiFive1 Rev B board has a 32MHz clock
	return (cycles / frequency) * 1000.0;
}

int main(void) {
	int hartid = metal_cpu_get_current_hartid();
	unsigned long long start_cycle_count, end_cycle_count;

	// Get the start cycle count
	if (metal_timer_get_cyclecount(hartid, &start_cycle_count) != 0) {
		printf("Failed to get the start cycle count.\n");
		return 1;
	}

	// Below is the function to measure the execution time of

	/** initialize SHA **/
	init_sha();

	/** test SHA-256 **/
	test_sha256();

	// Get the end cycle count
	if (metal_timer_get_cyclecount(hartid, &end_cycle_count) != 0) {
		printf("Failed to get the end cycle count.\n");
		return 1;
	}

	// Check for timer overflow
	unsigned long long elapsed_cycles;
	if (end_cycle_count >= start_cycle_count) {
		elapsed_cycles = end_cycle_count - start_cycle_count;
	} else {
		elapsed_cycles = (0xFFFFFFFFFFFFFFFF - start_cycle_count)
				+ end_cycle_count + 1;
	}

	// Convert clock cycle count to milliseconds
	double elapsed_ms = cycles_to_ms(elapsed_cycles);

	printf("Function execution time: %.3f ms\n", elapsed_ms);

	while (1)
		;

	return 0;

}
