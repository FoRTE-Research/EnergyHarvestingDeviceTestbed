/*******************************************************************
  This file contains the main method to run the hmac code in Arduino.
  This program can be used to run hmac code on Adafruit Metro M0 Express.
 *******************************************************************/
 
/** need to uncomment the board you are using **/
// #define msp432p401r
// #define riscv
#define adafruitm0express

#include "hmac_sha256.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SHA256_HASH_SIZE 32

void setup()
{
  Serial.begin(9600);
}

void loop()
{
#ifdef adafruitm0express
  /** Measure the starting time **/
  setup();
  unsigned long start, finished, elapsed;
  start = micros();
#endif

  const char* str_data = "Hello World!";
  const char* str_key = "super-secret-key";
  uint8_t out[SHA256_HASH_SIZE];
  char out_str[SHA256_HASH_SIZE * 2 + 1];
  unsigned i;

  // Call hmac-sha function
  hmac_sha256(str_key, strlen(str_key), str_data, strlen(str_data), &out,
              sizeof(out));

  // Convert `out` to string with printf
  memset(&out_str, 0, sizeof(out_str));
  for (i = 0; i < sizeof(out); i++) {
    snprintf(&out_str[i * 2], 3, "%02x", out[i]);
  }

  //     Print out the result
  printf("Message: %s\n", str_data);
  printf("Key: %s\n", str_key);
  printf("HMAC: %s\n", out_str);

  // This assertion fails if something went wrong
  assert(strncmp(
           out_str,
           "4b393abced1c497f8048860ba1ede46a23f1ff5209b18e9c428bddfbb690aad8",
           SHA256_HASH_SIZE * 2) == 0);

#ifdef adafruitm0express
  /** Calculate the elapsed time **/
  finished = micros();
  elapsed = finished - start;
  Serial.print("Time taken by the task: ");
  Serial.println(elapsed);

  // wait a second so as not to send massive amounts of data
  delay(1000);
#endif
}
