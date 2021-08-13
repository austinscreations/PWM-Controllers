// wifi setup information

#ifndef wifi_setup_H
#define wifi_setup_H

void settopics(){ // sets mqtt topics based on hostname
  // *** outputs *** //
  strcpy(clientoutput, host);
  strcat(clientoutput,"/LWT");

  // *** inputs ***  //
  strcpy(clientinput, host);
  strcat(clientinput,"/color");

  strcpy(clientinput2, host);
  strcat(clientinput2,"/flash");
  
  strcpy(clientinput3, host);
  strcat(clientinput3,"/fade");
  
  strcpy(clientinput4, host);
  strcat(clientinput4,"/config");

  
  out_heart = clientoutput;
  in_topic1 = clientinput;
  in_topic2 = clientinput2;
  in_topic3 = clientinput3;
  in_topic4 = clientinput4;

  Serial.println(out_heart);
  Serial.println("flash");
  Serial.println(in_topic1);
  Serial.println(in_topic2);
  Serial.println(in_topic3);
  Serial.println(in_topic4);
}


void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
   Serial.print("payload: [");
   Serial.print((char *)payload);
   Serial.println("]");

    if (strcmp(topic,"flash")==0){
    if ((char)payload[0] == '1') {ledState = HIGH;} // on
    if ((char)payload[0] == '0') {ledState = LOW;}  // off
    }

    if (strcmp(topic,in_topic4)==0){  // receiving config message
      String value = String((char*)payload);

      int iStart, iEnd;
      iStart = 0;
      iEnd = value.indexOf(',', iStart);
      configVAL1 = value.substring(iStart, iEnd).toInt(); // what strip number are we changing
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      configVAL2 = value.substring(iStart, iEnd).toInt(); // what type of strip is it.

      if (configVAL1 != 0)                                // make sure we aren't tryng to set strip zero (the code interface uses one based numbers)
      {
        Serial.print("Changing Strip #: ");
        Serial.println(configVAL1);

        Serial.print("Strip Uses ");
        Serial.print(configVAL2);
        Serial.println(" Channels");

        if (configVAL2 >= 1 && configVAL2 <= 5)
        {
          configArray[(configVAL1-1)] = {configVAL2};
          totalConfig++; //increase the total num of strips configured
        }
        else
        {
          Serial.println("Incompatible strip - use 1 - 5 channel LED strips");
        }
      }
      else
      {
       Serial.println("LED's are 1-based number - change your value");
      }
     }
     
if (strcmp(topic,in_topic1)==0){ // normal color set mode

  if (totalConfig != 0) // make sure an led strip has been configured
  {
    String value = String((char*)payload);

   int iStart, iEnd;
   iStart = 0;
   iEnd = value.indexOf(',', iStart);
   mqttNUM = value.substring(iStart, iEnd).toInt();
   Serial.print("LED #: ");
   Serial.println(mqttNUM);
   ledmode[(mqttNUM-1)] = 1;
   Serial.print("LED mode: ");
   Serial.println(ledmode[(mqttNUM-1)]);

   if (mqttNUM != 0) // valid strip num
   {
    if (configArray[(mqttNUM-1)] == 1) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 2) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 3) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 4) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 5) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC5[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
     Serial.print("Color 5: ");
     Serial.println(mqttC5[(mqttNUM-1)]);
    }
   }
   else
   {
    Serial.println("LED's are 1-based number - change your value");
   }

  }
  else
  {
    Serial.println("no LED strips configured");
  }
} // end of set normal color topic% = %hostname%/color

if (strcmp(topic,in_topic2)==0){ // flash color mode

  if (totalConfig != 0) // make sure an led strip has been configured
  {
    String value = String((char*)payload);

   int iStart, iEnd;
   iStart = 0;
   iEnd = value.indexOf(',', iStart);
   mqttNUM = value.substring(iStart, iEnd).toInt();
   Serial.print("LED #: ");
   Serial.println(mqttNUM);
   ledmode[(mqttNUM-1)] = 2; // set mode to flash
   Serial.print("LED mode: ");
   Serial.println(ledmode[(mqttNUM-1)]);

   if (mqttNUM != 0) // valid strip num
   {
    if (configArray[(mqttNUM-1)] == 1) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 2) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 3) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 4) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 5) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC5[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
     Serial.print("Color 5: ");
     Serial.println(mqttC5[(mqttNUM-1)]);
    }
   }
   else
   {
    Serial.println("LED's are 1-based number - change your value");
   }

  }
  else
  {
    Serial.println("no LED strips configured");
  }
} // end of set color flash topic% = %hostname%/flash


if (strcmp(topic,in_topic3)==0){ // fade color mode

  if (totalConfig != 0) // make sure an led strip has been configured
  {
    String value = String((char*)payload);

   int iStart, iEnd;
   iStart = 0;
   iEnd = value.indexOf(',', iStart);
   mqttNUM = value.substring(iStart, iEnd).toInt();
   Serial.print("LED #: ");
   Serial.println(mqttNUM);
   ledmode[(mqttNUM-1)] = 3;     // set mode to fade
   strip.fadereset((mqttNUM-1)); // reset the fade
   Serial.print("LED mode: ");
   Serial.println(ledmode[(mqttNUM-1)]);

   if (mqttNUM != 0) // valid strip num
   {
    if (configArray[(mqttNUM-1)] == 1) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 2) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 3) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 4) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
    }
    if (configArray[(mqttNUM-1)] == 5) 
    {
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC1[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC2[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC3[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC4[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     iStart = iEnd + 1;
     iEnd = value.indexOf(',', iStart);
     mqttC5[(mqttNUM-1)] = value.substring(iStart, iEnd).toInt();
     Serial.print("Color 1: ");
     Serial.println(mqttC1[(mqttNUM-1)]);
     Serial.print("Color 2: ");
     Serial.println(mqttC2[(mqttNUM-1)]);
     Serial.print("Color 3: ");
     Serial.println(mqttC3[(mqttNUM-1)]);
     Serial.print("Color 4: ");
     Serial.println(mqttC4[(mqttNUM-1)]);
     Serial.print("Color 5: ");
     Serial.println(mqttC5[(mqttNUM-1)]);
    }
   }
   else
   {
    Serial.println("LED's are 1-based number - change your value");
   }

  }
  else
  {
    Serial.println("no LED strips configured");
  }
} // end of set color fade topic% = %hostname%/fade

 
} // end of callback

void reconnect() {
  
  // Loop until we're reconnected
  while (!client.connected()) {
   

    Serial.print("Attempting MQTT connection...");
    if (client.connect(host,mqtt_username,mqtt_password,out_heart, mqtt_lwt_qos, mqtt_lwt_retain, "0")) {
//    if (client.connect(host,out_heart, mqtt_lwt_qos, mqtt_lwt_retain, "0")){                                      **** may need to change me with the line above if not using user / password
      Serial.println("mqtt connected");
      // Once connected, publish an announcement...
      strcpy(connectphrase, "connected = ");
      strcat(connectphrase, host);
      strcat(connectphrase, "  IP Address = ");
      const char * c = IPaddress.c_str();
      strcat(connectphrase, c); // ip address
      const char* phrase = connectphrase;
      client.publish("outTopic",phrase);
      byte lwt_payload[] = { '1' };
      client.publish(out_heart, lwt_payload, 1, mqtt_lwt_retain);
      // ... and resubscribe
      client.subscribe("flash");
      client.subscribe(in_topic1);
      client.subscribe(in_topic2);
      client.subscribe(in_topic3);
      client.subscribe(in_topic4);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
//       Wait 5 seconds before retrying
      delay(5000);
     }
  }
}

void setup_wifi() {
  delay(10);
//   We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  IPaddress =  WiFi.localIP().toString();
}

#endif
