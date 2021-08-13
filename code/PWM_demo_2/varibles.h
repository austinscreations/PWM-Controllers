/* 
 *  global varibles
 *  nothing here should need to be changed
 *  
 */

#ifndef varibles_H
#define varibles_H

/* MQTT */
const char* out_heart = "-";
const char* in_topic1 = "-";
const char* in_topic2 = "-";
const char* in_topic3 = "-";
const char* in_topic4 = "-";
char clientoutput[100];
char clientinput[100];
char clientinput2[100];
char clientinput3[100];
char clientinput4[100];
char connectphrase[140]; // publishes to 'outTopic' when connected
String IPaddress;

uint8_t configArray[17] = {0};  // stores the strip type - over ridden via mqtt config

uint8_t totalConfig = 0;        // number of led strips that are configured
uint8_t offsetCALC = 0;         // used to calulate the strip offset
uint8_t configVAL1;             // used for incoming mqtt strip num  in config
uint8_t configVAL2;             // used for incoming mqtt strip type in config

uint8_t mqttNUM = 0;            // incoming num   value from mqtt
uint8_t mqttC1[17] = {0};       // incoming color value from mqtt
uint8_t mqttC2[17] = {0};       // incoming color value from mqtt
uint8_t mqttC3[17] = {0};       // incoming color value from mqtt
uint8_t mqttC4[17] = {0};       // incoming color value from mqtt
uint8_t mqttC5[17] = {0};       // incoming color value from mqtt

const uint8_t mqtt_lwt_qos     = 0;
const uint8_t mqtt_lwt_retain  = 1;

/* led control varibles */
uint8_t ledmode[17] = {0};             // mode the led strip is in
int ledState = LOW;                    // ledState used to set the LED flash
unsigned long crossfadePREV[17] = {0}; // last time fading in micros()


#endif
