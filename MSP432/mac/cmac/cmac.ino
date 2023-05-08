/*******************************************************************
  This file contains the main method to run the cmac code in Arduino.
  This program can be used to run cmac code on Adafruit Metro M0 Express.
 *******************************************************************/

/** need to uncomment the board you are using **/
// #define msp432p401r
// #define riscv
#define adafruitm0express

#include <string.h>

#include "cmac.h"
#include "utils.h"

void run();

void setup()
{
  Serial.begin(9600);
}

void run()
{
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

  aes_cmac(message, strlen((char *)message) + 1, (unsigned char *)out, key);
  //    printf("%sAES-128-CMAC Result%s\n", ACCENTCOLOR, DEFAULT);
  //    print_bytes(out, 16);
}

void loop()
{
#ifdef adafruitm0express
  /** Measure the starting time **/
  setup();
  unsigned long start;
  unsigned long finished;
  unsigned long elapsed;
  start = micros();
#endif

  run();

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
