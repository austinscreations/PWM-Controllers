// h file v0.1.0

/*!
 *
 * 
 *
 *  BSD license, all text above must be included in any redistribution
 */



#ifndef ledPWM_H
#define ledPWM_H

#include <Arduino.h>

/*!
 *  @brief  Class that stores state and functions for interacting with PCA9685
 * PWM chip
 */
class PWMDriver {
public:
  PWMDriver();
  void begin(uint8_t g1,uint8_t g2,uint8_t g3,uint8_t g4,uint8_t g5);

  void fadereset();

  void LED(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5);

  void crossfadeBUTTON(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5);

  void crossfade(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5);
  
  uint8_t complete = false;



private:
  void clear();
  const int channelarray[5] = {0,2,4,6,8};
  int ledarray[5] = {0,0,0,0,0};
  const int freq = 5000;
  const int resolution = 8;
  
  int calculateVal(int step, int val, int i);
  int calculateStep(int prevValue, int endValue);

  int i = 0;
  int prev1 = {};
  int prev2 = {};
  int prev3 = {};
  int prev4 = {};
  int prev5 = {};
  int c1Val = {};
  int c2Val = {}; 
  int c3Val = {};
  int c4Val = {};
  int c5Val = {};
  int step1;
  int step2; 
  int step3;
  int step4;
  int step5;
};

#endif
