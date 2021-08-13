/*
 * started 2021-08-11 - complete 2021-08-13
 * 
 * goal to have all led modes working via mqtt                              // done
 * 
 * TASKS
 * update library to work with new offset scheme                            // done
 * test with RGBCCT and CCT                                                 // done
 * add fade mode                                                            // done
 * add flash mode                                                           // done
 * 
 *  option - set color    (topic = %hostname%/color; payload = strip#, C#) (repeat C# for the number of channels in a strip) eg RGB  = strip#,C1,C2,C3
 *  option fade to color  (topic = %hostname%/fade;  payload = strip#, C#)
 *  option Color to Flash (topic = %hostname%/flash; payload = strip#, C#)
 *  
 *  config led strip      (topic = %hostname%/config; payload = strip#, # of channels used (1-5))
 *
 *  online status can be found with %hostname%/LWT 
 *  
 *  first online connection + IPaddress = /outTopic
 * 
 */

#include <ESP8266WiFi.h>              // gotta have wifi on your esp8266
#include <PubSubClient.h>             // For MQTT
#include "ledPWM.h"                   // embedded led driver library
#include "config.h"
#include "varibles.h"

PWMDriver strip = PWMDriver(0x40);

WiFiClient espClient;
PubSubClient client(espClient);

#include "wifi_setup.h"


void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(200);
  Serial.println("\n starting");

  settopics();
  WiFi.hostname(host);
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  strip.begin();

  Serial.println("setup done");

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
   client.loop();


for (uint8_t x = 0; x < totalConfig; x++)
{
  if (ledmode[x] == 3)                                                                         // fade the lights ****
  {
    if ((micros() - crossfadePREV[x]) > fadespeed)                                             // check if it's time to fade
    {
      if (configArray[x] == 1) 
      {
        strip.crossfadeBUTTON(x,offsetCALC,mqttC1[x]);                                         // single strip (strip num, offset, C1)
      }
      if (configArray[x] == 2) 
      {
        strip.crossfadeBUTTON(x,offsetCALC,mqttC1[x],mqttC2[x]);                               // CCT strip (strip num, offset, C1, C2)
      }
      if (configArray[x] == 3) 
      {
         strip.crossfadeBUTTON(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x]);                    // RGB strip (strip num, offset, C1, C2, C3)
      }
      if (configArray[x] == 4) 
      {
        strip.crossfadeBUTTON(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x]);           // RGBW strip (strip num, offset, C1, C2, C3, C4)
      }
      if (configArray[x] == 5) 
      {
        strip.crossfadeBUTTON(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x],mqttC5[x]); // RGBCCT strip (strip num, offset, C1, C2, C3, C4, C5)
      }
      crossfadePREV[x] = micros();
    }
  }


  if (ledmode[x] == 2)                                                              // flash led strip ****
  {
    if (configArray[x] == 1) 
    {
      if (ledState == HIGH)
      {
        strip.LED(x,offsetCALC,mqttC1[x]);                                          // single strip (strip num, offset, C1)
      }
      else
      {
        strip.LED(x,offsetCALC,0);                                                  // off
      }
    }
    if (configArray[x] == 2) 
    {
      if (ledState == HIGH)
      {
        strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x]);                                // CCT strip (strip num, offset, C1, C2)
      }
      else
      {
        strip.LED(x,offsetCALC,0,0);                                                // off
      }
    }
    if (configArray[x] == 3) 
    {
      if (ledState == HIGH)
      {
        strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x]);                      // RGB strip (strip num, offset, C1, C2, C3)
      }
      else
      {
        strip.LED(x,offsetCALC,0,0,0);                                              // off
      }
    }
    if (configArray[x] == 4) 
    {
      if (ledState == HIGH)
      {
        strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x]);            // RGBW strip (strip num, offset, C1, C2, C3, C4)
      }
      else
      {
        strip.LED(x,offsetCALC,0,0,0,0);                                            // off
      }
    }
    if (configArray[x] == 5) 
    {
      if (ledState == HIGH)
      {
        strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x],mqttC5[x]); // RGBCCT strip (strip num, offset, C1, C2, C3, C4, C5)
      }
      else
      {
        strip.LED(x,offsetCALC,0,0,0,0,0);                                         // off
      }
    }
  }

  
  if (ledmode[x] == 1)                                                           // turn the led on - normal color ****
  {
    if (configArray[x] == 1) 
    {
      strip.LED(x,offsetCALC,mqttC1[x]);                                         // single strip (strip num, offset, C1)
    }
    if (configArray[x] == 2) 
    {
      strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x]);                               // CCT strip (strip num, offset, C1, C2)
    }
    if (configArray[x] == 3) 
    {
       strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x]);                    // RGB strip (strip num, offset, C1, C2, C3)
    }
    if (configArray[x] == 4) 
    {
      strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x]);           // RGBW strip (strip num, offset, C1, C2, C3, C4)
    }
    if (configArray[x] == 5) 
    {
      strip.LED(x,offsetCALC,mqttC1[x],mqttC2[x],mqttC3[x],mqttC4[x],mqttC5[x]); // RGBCCT strip (strip num, offset, C1, C2, C3, C4, C5)
    }
  }
  offsetCALC = offsetCALC + configArray[x]; // increase offset value
}
offsetCALC = 0; // reset offset value
  


}
