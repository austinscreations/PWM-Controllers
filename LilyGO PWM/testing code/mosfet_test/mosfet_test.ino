
/* 
 *            lilyGO - tiny pico
 * channel 1 GPIO_14
 * channel 2 GPIO_04
 * channel 3 GPIO_12 / 27
 * channel 4 GPIO_15
 * channel 5 GPIO_16 / 21
 * 
 */


const int ledarray[] = {14,04,12,15,16};
//const int ledarray[] = {14,04,27,15,21};

const int channelarray[] = {0,2,4,6,8};

const int freq = 5000;
const int resolution = 8;


void setup() {



 for(int y = 0; y < 6; y++)
 { 
   ledcSetup(channelarray[y], freq, resolution);
   ledcAttachPin(ledarray[y], channelarray[y]);
 }

}

void loop() {


 for(int x = 0; x < 6; x++)
 { 
   // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle < 255; dutyCycle++)
  {   
    // changing the LED brightness with PWM
    ledcWrite(channelarray[x], dutyCycle);
    delay(5);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    // changing the LED brightness with PWM
    ledcWrite(channelarray[x], dutyCycle);
    delay(5);
  }
 }

}
