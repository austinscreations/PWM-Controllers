/* Handles Wifi and AP mode - ON / OFF and timeout */

#ifndef wifi_h
#define wifi_h

uint8_t wifi_confirmed = false;
uint8_t ap_msg_timeout = false;
uint8_t ap_start = false;
uint8_t ap_connected = false;             //returned from WiFi.softAPgetStationNum()
unsigned long prevAPmillis;
unsigned long wifimillis;
unsigned long timer;
unsigned long checkup;

void access_point_init() 
{
    WiFi.softAPdisconnect(false);
    delay(200);
//      WiFi.softAP(AP_SSID, AP_PASS);
    if (strcmp(AP_SSID, "0") == 0)   // AP SSID hasn't been defined used host as our AP SSID
    {
     strcpy(AP_SSID, host);
    }
    WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CON);
    Serial.print("IP address for network ");
    Serial.print(AP_SSID);
    Serial.print(" : ");
    Serial.println(WiFi.softAPIP());
    ap_start = true;
}

// start connecting to a WiFi network
void setup_wifi() 
{
  WiFi.hostname(host);
  delay(10);
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  if (strcmp(password, "0") == 0) // non-password protected wifi
  {
    WiFi.begin(ssid);
  }
  else
  {
    WiFi.begin(ssid, password);
  }
  prevAPmillis = millis();
  }


// check to see if we are connected to wifi
void wifi_checkup()
{
   if (millis() - checkup > 3000)
   {
     checkup = millis();
  if (WiFi.status() != WL_CONNECTED) 
  {
    
    wifi_confirmed = false;
    if (ap_start == false)
    {
     if (millis() - prevAPmillis > 30000)  // start AP mode
     {
      Serial.println("\n wifi not connecting - starting AP");
      ap_msg_timeout = false;
      access_point_init(); // start AP for config
     }
    }
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    if (wifi_confirmed == false){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
    wifi_confirmed = true;
    }
    prevAPmillis = millis();

    if (ap_connected == false) // no one is connected to AP
    {
       if (ap_msg_timeout == false)
       {
           WiFi.softAPdisconnect(true);
           Serial.println("AP mode disabled - wifi restored");
           ap_msg_timeout = true;
       }
    }
  }
  wifimillis = millis();

// this works - shows number of stations connected to AP wifi - turns off ap when conencted to wifi - and no clients connected
  if ((millis() - timer) > 5000) 
{
  if (ap_start == true)
  {
//    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    ap_connected = WiFi.softAPgetStationNum();
  }
  timer = millis();
   }
  }
}

void wifi_start() {
  WiFi.mode(WIFI_AP_STA);
  
  if (strcmp(ssid, "0") == 0)
  {
    Serial.println("wifi not defined - starting AP");
    access_point_init(); // start AP for config
  }
  else
  {
//    Serial.println(ssid);
    setup_wifi(); // start regular wifi
  }

}



#endif
