#ifndef config_h
#define config_h

/* ----------------- General config -------------------------------- */


/* Serial */
#define SERIAL_BAUD_RATE       115200


/* Varibles here are filled in by the config system */
char        host[32];
char        ssid[32];
char        password[64];

char        AP_SSID[32];
char        AP_PASS[64];
uint8_t     AP_CHANNEL  = 1; // not written over
uint8_t     AP_HIDDEN;
uint8_t     AP_MAX_CON  = 1; // not written over

char        mqtt_broker[32];
uint16_t    mqtt_port;
char        mqtt_username[32];
char        mqtt_password[32];

uint8_t     darkState;
char        htmltitle[32];
char        htmltype[32];
char        htmlcolor[10];
char        htmlhover[10];

uint16_t    fadespeed;


#endif
