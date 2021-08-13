/* This page and fuctions handle filling in %varibles% in HTML webpages*/

#ifndef processing_items_h
#define processing_items_h

#include "CSS.h"
#include "SCRIPTS.h"
#include "MCU_functions.h"

uint8_t deviceREBOOTED = true;

String DeviceID()
{
#if defined(DeviceName)
  String id = STR(DeviceName);
#else
  String id = host;
#endif
  return id;
}

String info_memsketch(){
    String memsketch = ((String)(ESP.getSketchSize())) +  " / " + ((String)(ESP.getSketchSize()+ESP.getFreeSketchSpace())) + "  Used / Total";
    return memsketch;
   }

String ip3string(IPAddress ip) {
  String ret = String(ip[0]) + "." +  String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  return ret;
}

String processor(const String& var){ // Change placeholders on webpage

  if(var == "The_CSS")
  {
   return CSS_STYLE;
  }
  
  if(var == "The_SCRIPTS")
  {
   return CSS_SCRIPTS;
  }

  if(var == "heart"){
    String hearting = "";
    hearting += out_heart;
    return hearting;
  }

  if(var == "flash"){
    String flashing = "flash";
    return flashing;
  }

  if(var == "topic1"){
    String topic1ing = "";
    topic1ing += in_topic1;
    return topic1ing;
  }

  if(var == "topic2"){
    String topic2ing = "";
    topic2ing += in_topic2;
    return topic2ing;
  }

  if(var == "topic3"){
    String topic3ing = "";
    topic3ing += in_topic3;
    return topic3ing;
  }

  if(var == "topic4"){
    String topic4ing = "";
    topic4ing += in_topic4;
    return topic4ing;
  }


  if(var == "memsketch")
    {
      String infos = info_memsketch();
     return infos;
    }

  if(var == "title"){
    String titleing = "";
    titleing += htmltitle;
    return titleing;
  }
  
  if(var == "dark"){
    String dark = "";
    if (darkState == false){
      dark += "body { background-color: white; color: black; }";
    }else{
      dark += "body { background-color: black; color: white; }";
    }
    return dark;
  }
  
  if(var == "online"){
    String online = "";
    if (WiFi.status() == WL_CONNECTED) 
      {
        online += "background:green";
      }
      else
      {
        online += "background:orange";
      }
    return online;
  }
  
  if(var == "color"){
    String coloring = "";
    coloring +=  htmlcolor;
    return coloring;
  }
  
  if(var == "hover"){
    String hovering = "";
    hovering +=  htmlhover;
    return hovering;
  }
  if(var == "ipplaceholder"){
    String iping = "";
    iping += ip3string(WiFi.localIP());
    return iping;
  }
  if(var == "macplaceholder"){
    String macing = "";
    macing +=  WiFi.macAddress();
    return macing;
  }
  if(var == "IDplaceholder"){
    String IDing = "";
    IDing +=   DeviceID();
    return IDing;
  }
  if(var == "processorplaceholder"){
    String PROing = "";
                #if defined(ESP8266)
                      PROing += "ESP8266";
                #elif defined(ESP32)
                      PROing +=  "ESP32";
                #endif
    return PROing;
  }
  
  if(var == "type"){
    String typeing = "";
     typeing += htmltype;
    return typeing;
  }
  
  if (var == "errorplaceholder")
    {
        String erroring = "";
        if (deviceREBOOTED == false){
         erroring += "";
        } else {
         erroring += "Device Rebooted";
         deviceREBOOTED = false;
            erroring += " (";

         #if defined(ESP8266)
            String RebootReason =
                ESP.getResetReason().c_str();
          #elif defined(ESP32)
            String RebootReason =
                return_reset_reason(rtc_get_reset_reason(0));
            erroring += RebootReason;
            erroring += "/";
            RebootReason =
                return_reset_reason(rtc_get_reset_reason(1));
          #endif
            erroring += RebootReason;
            erroring += ")";
        }
        return erroring;
    }

  return String();
}


#endif
