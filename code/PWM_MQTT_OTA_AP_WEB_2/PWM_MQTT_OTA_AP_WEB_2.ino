
/* 
 * started 2021-08-13 - working
 * 
 * goal to have AP config and web interface                                // 
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
 */

#include "FS.h"
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>

#if defined(ESP8266)
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
    #include "flash_hal.h"
    #include <LittleFS.h>
#elif defined(ESP32)
    #include "WiFi.h"
    #include "AsyncTCP.h"
    #include "Update.h"
    #include "esp_int_wdt.h"
    #include "esp_task_wdt.h"
    #include "LITTLEFS.h"
#endif

#include <PubSubClient.h>       // For MQTT

#include "ledPWM.h"             // embedded led driver library
#include "config.h"             // config information      - some can be changed only on upload - others are changed via web config
#include "factory_settings.h"   // factory reset config
#include "varibles.h"           // regular global varibles - shouldn't need editing

PWMDriver strip = PWMDriver(0x40);

WiFiClient espClient;
PubSubClient client(espClient);

#include "mqtt_setup.h"

/* WEB PAGES */
#include "homepage.h"           // website home page
#include "management.h"         // Website OTA page
#include "config_page.h"        // ESP html configuration page
#include "failed.h"             // Something failed webpage
#include "reboot.h"             // Website - ESP rebooting
#include "finished.h"           // OTA success Webpage

AsyncWebServer server(80);      // declare ASYNC server library

#include "wifisave.h"           // Saving new Config information
#include "processing_items.h"   // processor for webpage varibles
#include "customserver.h"       // manages the ASYNC server webpage serving
#include "wifi.h"               // manages the wifi and AP conenctions



void setup() {

  Serial.begin(SERIAL_BAUD_RATE);
  delay(200);
  Serial.println("\n Starting");

  parameterSETUP();        // wifisave.h            - set up saved / factory config

  settopics();             // mqtt_setup.h          - set the mqtt topics

  wifi_start();            // wifi.h - start wifi   - will start AP / WiFi as needed
  
  Serial.println("Starting ASYNC server");
  customInit();             // customserver.h        - start server - starts ASYNC server

  if (strcmp(mqtt_broker, "0") == 0)                 // no broker declared
  {Serial.println("no broker declared");}
  else                                               // broker declared
  {
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
  }

  strip.begin(); // start led PWM driver
}

void loop() {
  wifi_checkup();                        // wifi.h         - checks if wifi is still connected and starts AP as needed
  if (restartRequired){OTA_Restart();}   // customserver.h - checks if the esp needs a reboot - done via webpage / OTA
  
  if (WiFi.status() == WL_CONNECTED)
  {
    if (strcmp(mqtt_broker, "0") == 0) // no broker declared
    {}
    else                               // broker declared
    {
      if (!client.connected()) 
      {
        reconnect();
      }
     client.loop();
    }
  }
  
  /* 
   *  controls LED's
   */

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
