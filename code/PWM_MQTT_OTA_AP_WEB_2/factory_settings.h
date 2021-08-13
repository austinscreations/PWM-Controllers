/* Factory settings are saved here */

/* using factory reset button will revert to these settings */

#ifndef factory_settings_h
#define factory_settings_h

/* Device name / hostname - Hostname may not work on all DCHP setups */
char       hostFACTORY[32]           = "LEDcontrolFactory";

/* WIFI */
char       ssidFACTORY[32]           = "0";            // unconfigured ssid
char       passwordFACTORY[64]       = "0";            // wifi password

/* AP */
char       AP_SSIDFACTORY[32]         = "0";            // will revert to using host
char       AP_PASSFACTORY[64]         = "SUMpassword";  // AP password                                   *** Minimum 8 charcter value max 63 (64 with \n)
uint8_t    AP_HIDDENFACTORY           = 0;              // AP SSID brodcast                              hidden = 1

/* MQTT */
char       mqtt_brokerFACTORY[32]    = "0";            // IP address or host name of your MQTT broker
uint16_t   mqtt_portFACTORY          = 1883;           // port for MQTT broker
char       mqtt_usernameFACTORY[32]  = "0";            // undefined username for mqtt                  won't use a username or password in this case
char       mqtt_passwordFACTORY[32]  = "0";            // template password for mqtt user

/* HTML */
uint8_t   darkStateFACTORY           = 1;
char      htmltitleFACTORY[32]       = "LEDcontrol";   // main title on the top of webpage          
char      htmltypeFACTORY[32]        = "Factory";      // Device type on the bottom of webpage     
char      htmlcolorFACTORY[10]       = "#176fc1";      // main HTML webpage color                       Superhouse.tv color
char      htmlhoverFACTORY[10]       = "#00a5b4";      // html color for hovering over a menu button    Superhouse.tv color

/* LEDs */ 
uint16_t  fadespeedFACTORY           = 200;            // fade animation speed in micros()

#endif
