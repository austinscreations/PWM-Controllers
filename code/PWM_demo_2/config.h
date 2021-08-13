/* ----------------- General config -------------------------------- */
/* Serial */
#define SERIAL_BAUD_RATE       115200

/* LED's */
uint8_t fadespeed              = 200;               // fade animation speed in micros()

/* WIFI */ 
const char* host               = "LEDcontrol";      // host name to show on wifi network && mqtt topics
const char* ssid               = "***";
const char* password           = "****";

/* MQTT */
const char*   mqtt_broker      = "192.168.0.54";    // IP address or host name of your MQTT broker
const int     mqtt_port        = 1883;

/* if not using a user / password for mqtt there is a line to comment / uncomment in wifi_setup.h */
const char*  mqtt_username     = "****";
const char*  mqtt_password     = "****";
