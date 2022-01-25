#include "ledPWM.h"                   // embeded library for 5 mosfets on esp32                  

// Supported LED modes
#define LED_MODE_NONE               0
#define LED_MODE_COLOUR             1
#define LED_MODE_FADE               2
#define LED_MODE_FLASH              3

// Default fade interval (microseconds)
#define DEFAULT_FADE_INTERVAL_US    500L;

/*-------------------------- Internal datatypes --------------------------*/


uint8_t mode = LED_MODE_NONE;
uint8_t colour[5];
uint32_t lastCrossfade;

/*--------------------------- Global Variables ---------------------------*/
// How long between each fade step
uint32_t g_fade_interval_us = DEFAULT_FADE_INTERVAL_US;

// Flashing state for any strips in flash mode
uint8_t g_flash_state = LOW;

// PWM Control library
PWMDriver pwmDriver;


/**
  Setup
*/
void setup() {


  pwmDriver.begin(14,04,12,15,16);

  pwmDriver.LED(255, colour[1], colour[2], colour[3], colour[4]);

}

void loop() {
  // Check our MQTT broker connection is still ok

//  LED_loop();

}

/**
   Handle the LEDs
*/
void LED_loop()
{
  if (mode == LED_MODE_COLOUR)
  {
  // colour
  ledColour();
  }
  else if (mode == LED_MODE_FADE)
  {
  // fade
  ledFade();
  }
  else if (mode == LED_MODE_FLASH)
  {
  // flash
  ledFlash();
  }
}

void ledColour()
{
  pwmDriver.LED(colour[0], colour[1], colour[2], colour[3], colour[4]);
  
}

void ledFade()
{
  if ((micros() - lastCrossfade) > g_fade_interval_us)
  {    
    pwmDriver.crossfadeBUTTON(colour[0], colour[1], colour[2], colour[3], colour[4]);
    lastCrossfade = micros();
  }
}

void ledFlash()
{
  if (g_flash_state == HIGH)
  {
    pwmDriver.LED(colour[0], colour[1], colour[2], colour[3], colour[4]);
  }
  else
  {
    pwmDriver.LED(0, 0, 0, 0, 0);
  }
}
