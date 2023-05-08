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
#include <assert.h>

#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/mac/hmac/hmac_sha256.h"
#include "/Users/zeezooryu/wsFreedomStudio/EmbeddedCrypto/mac/hmac/hmac_sha256.c"

#define SHA256_HASH_SIZE 32

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
	const char *str_data = "Hello World!";
	const char *str_key = "super-secret-key";
	uint8_t out[SHA256_HASH_SIZE];
	char out_str[SHA256_HASH_SIZE * 2 + 1];
	unsigned i;

	// Call hmac-sha function
	hmac_sha256(str_key, strlen(str_key), str_data, strlen(str_data), &out,
			sizeof(out));

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
