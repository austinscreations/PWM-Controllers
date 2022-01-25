// cpp file v0.1.0

/*!
 *
 * This library is based of one created by Adafruit for the PCA9685,
 * it has been modified for easy control of RGB led strips via mosfets
 *
 *  @file Adafruit_PWMServoDriver.cpp
 *
 *  @mainpage Adafruit 16-channel PWM & Servo driver
 *
 *  @section intro_sec Introduction
 *
 *  This is a library for the 16-channel PWM & Servo driver.
 *
 *  Designed specifically to work with the Adafruit PWM & Servo driver.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/815
 *
 *  These displays use I2C to communicate, 2 pins are required to interface.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  @section author Author
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  @section license License
 *
 *  BSD license, all text above must be included in any redistribution
 */



#include "ledPWM.h"
#include <Wire.h>


PWMDriver::PWMDriver() {}


void PWMDriver::begin(uint8_t g1,uint8_t g2,uint8_t g3,uint8_t g4,uint8_t g5) {
ledarray[0] = g1;
ledarray[1] = g2;
ledarray[2] = g3;
ledarray[3] = g4;
ledarray[4] = g5;
  
 for(int y = 0; y < 6; y++)
 { 
   ledcSetup(channelarray[y], freq, resolution);
   ledcAttachPin(ledarray[y], channelarray[y]);
 }

clear();
}

/*
 * LED PWM animation functions
 */
void PWMDriver::clear(){
for (int x = 0; x <= 16; x++) {
    ledcWrite(channelarray[x], 0);
    prev1 = 0;
    prev2 = 0;
    prev3 = 0;
    prev4 = 0;
    prev5 = 0;
    c1Val = 0;
    c2Val = 0;
    c3Val = 0;
    c4Val = 0;
    c5Val = 0;
}}

int PWMDriver::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}


/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1. 
*  (R, G, and B are each calculated separately.)
*/

int PWMDriver::calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a     value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

void PWMDriver::fadereset(){
    i = 0;
  prev1 = c1Val; 
  prev2 = c2Val; 
  prev3 = c3Val;
  prev4 = c4Val;
  prev5 = c5Val;
}

/*
 * 5 channel strip control
 */

void PWMDriver::crossfade(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5) {

  int step1 = calculateStep(prev1, c1);
  int step2 = calculateStep(prev2, c2); 
  int step3 = calculateStep(prev3, c3);
  int step4 = calculateStep(prev4, c4);
  int step5 = calculateStep(prev5, c5);

    c1Val = calculateVal(step1, c1Val, i);
    c2Val = calculateVal(step2, c2Val, i);
    c3Val = calculateVal(step3, c3Val, i);
    c4Val = calculateVal(step4, c4Val, i);
    c5Val = calculateVal(step5, c5Val, i);

 ledcWrite(channelarray[0], c1Val);
 ledcWrite(channelarray[1], c2Val);
 ledcWrite(channelarray[2], c3Val);
 ledcWrite(channelarray[3], c4Val);
 ledcWrite(channelarray[4], c5Val);
    

if (i >= 1020){
complete = {true};
fadereset();
}else{
  i++;
}
}

void PWMDriver::crossfadeBUTTON(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5) {

  int step1 = calculateStep(prev1, c1);
  int step2 = calculateStep(prev2, c2); 
  int step3 = calculateStep(prev3, c3);
  int step4 = calculateStep(prev4, c4);
  int step5 = calculateStep(prev5, c5);

    c1Val = calculateVal(step1, c1Val, i);
    c2Val = calculateVal(step2, c2Val, i);
    c3Val = calculateVal(step3, c3Val, i);
    c4Val = calculateVal(step4, c4Val, i);
    c5Val = calculateVal(step5, c5Val, i);

 ledcWrite(channelarray[0], c1Val);
 ledcWrite(channelarray[1], c2Val);
 ledcWrite(channelarray[2], c3Val);
 ledcWrite(channelarray[3], c4Val);
 ledcWrite(channelarray[4], c5Val);

if (i <= 1020){
complete = {true};
fadereset();
}else{
  i++;
}
}

void PWMDriver::LED(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5){
 
 ledcWrite(channelarray[0], c1);
 ledcWrite(channelarray[1], c2);
 ledcWrite(channelarray[2], c3);
 ledcWrite(channelarray[3], c4);
 ledcWrite(channelarray[4], c5);

prev1 = c1;
prev2 = c2;
prev3 = c3;
prev4 = c4;
prev5 = c5;
c1Val = c1;
c2Val = c2;
c3Val = c3;
c4Val = c4;
c5Val = c5;
}
