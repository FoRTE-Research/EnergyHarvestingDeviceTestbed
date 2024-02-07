/* This is come with sifive board from sparkfun and we are making it work or our board*/


#include <stdio.h>      //include Serial Library
#include <time.h>       //include Time library
#include <metal/gpio.h> //include GPIO library, https://sifive.github.io/freedom-metal-docs/apiref/gpio.html


void delay(int number_of_microseconds){

// Converting time into multiples of a hundred nS
int hundred_ns = 10 * number_of_microseconds;

// Storing start time
clock_t start_time = clock();

// looping till required time is not achieved
while (clock() < start_time + hundred_ns);

}

int main (void) {

  struct metal_gpio *led0;


  //Get gpio device handle, i.e.) define IC pin here where IC's GPIO = 5/SPI.CLK
  led0 = metal_gpio_get_device(0);
  metal_gpio_disable_input(led0, 5); // We are sending stuff out.
  metal_gpio_enable_output(led0, 5);
  metal_gpio_disable_pinmux(led0, 5);

  //Turn ON pin
//  metal_gpio_set_pin(led0, 5, 1);
  while (1) {
      //Turn OFF pin
      metal_gpio_set_pin(led0, 5, 0); // of
      delay(20000);
      metal_gpio_set_pin(led0, 5, 1);
      delay(20000);
  }
  return 0;
}
