//Uncomment #define USART_LED below to test the USART functionality
#define USART_LED

#include <atmel_start.h>
#include <hal_gpio.h>
#include <hal_delay.h>

//115200 Baud rate
static const uint8_t welcoming_str[] = "Hello world in USART console.\r\n";

static uint16_t x = 0;
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	printf("%s", welcoming_str);
	/* Replace with your application code */
	while (1) {
		++x;
		printf("%d\r\n", x);
		gpio_toggle_pin_level(LED0);
		delay_ms(500);
	}
}
