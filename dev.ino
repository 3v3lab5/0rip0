

int wifi_connect(int WIFI_STATE)
{

  mqttClient.loop();
  const char* DRIPO_NAME = "DRIPO-%d";

  sprintf(id, DRIPO_NAME, ESP.getChipId());


  if (WIFI_STATE == 1)
  {
    if (SPIFFS.begin()) {
      // Serial.println("mounted file system");
      if (SPIFFS.exists("/config.json")) {
        //file exists, reading and loading
        //   Serial.println("reading config file");
        File configFile = SPIFFS.open("/config.json", "r");
        if (configFile) {
          //  Serial.println("opened config file");
          size_t size = configFile.size();
          // Allocate a buffer to store contents of the file.
          std::unique_ptr<char[]> buf(new char[size]);

          configFile.readBytes(buf.get(), size);
          DynamicJsonBuffer jsonBuffer;
          JsonObject& json = jsonBuffer.parseObject(buf.get());
          //   json.printTo(Serial);
          if (json.success()) {
            //    Serial.println("\nparsed json");

            strcpy(mqtt_server, json["mqtt_server"]);
            //   strcpy(mqtt_port, json["mqtt_port"]);

          } else {
            //   Serial.println("failed to load json config");
          }
        }
      }
    } else {
      Serial.println("failed to mount FS");
    }

    // WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    // WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
    WiFiManager wifiManager;
    //  wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.setConnectTimeout(10);
    wifiManager.setConfigPortalTimeout(1);
    // WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    //  wifiManager.addParameter(&custom_mqtt_server);
    //  wifiManager.addParameter(&custom_mqtt_port);
    //  mqtt_server = custom_mqtt_server.getValue();


    // void configModeCallback (WiFiManager *myWiFiManager);
    //wifiManager.setAPCallback(configModeCallback);

    if (!wifiManager.autoConnect(id)) {

      WiFi.mode(WIFI_OFF);
      return 2;
    }



  }
  else if (WIFI_STATE == 2)
  {
       if ( WiFi.status() == WL_CONNECTED ) {
if (!mqttClient.connected()) {

mqtt_reconnect();

   }   
   return 2;
    }

    //    if(sleep==false)
    //{
    ////
    //// // wifi_set_sleep_type(MODEM_SLEEP_T);
    //  wifi_fpm_open();
    //wifi_fpm_do_sleep(26843455);
    //delay(500);
    //sleep = true;
    //}
    return 2;

  }



  else if (WIFI_STATE == 4) {
    //    mqttClient.loop();
    //
    //    const char* DRIPO_NAME = "DRIPO-%d";
    //
    //    sprintf(id, DRIPO_NAME, ESP.getChipId());
    //
    //    WiFiManager wifiManager;
    //    wifiManager.setConnectTimeout(10);
    WiFi.mode(WIFI_OFF);
    WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    WiFiManager wifiManager_Ondemand;
    wifiManager_Ondemand.setAPCallback(configModeCallback);
    wifiManager_Ondemand.setConfigPortalTimeout(150);
    wifiManager_Ondemand.addParameter(&custom_mqtt_server);
    wifiManager_Ondemand.setConfigPortalExitable(funct);
    if (!wifiManager_Ondemand.startConfigPortal(id)) {
      //      Serial.println("failed to connect and hit timeout");
      //      delay(3000);
      //      //reset and try again, or maybe put it to deep sleep
      //      ESP.reset();
      //      delay(5000);
      WiFi.mode(WIFI_OFF);

    }


    //   mqtt_server = custom_mqtt_server.getValue();
    strcpy(mqtt_server, custom_mqtt_server.getValue());


    //  Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      //    Serial.println("failed to open config file for writing");
    }

    //  json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();

    return 2;
  }
  else  if (WIFI_STATE == 5)

  {
#define FPM_SLEEP_MAX_TIME 0xFFFFFFF

    wifi_set_sleep_type(MODEM_SLEEP_T);
    wifi_station_disconnect();
    wifi_set_opmode(NULL_MODE); // set WiFi mode to null mode
    wifi_fpm_open(); // enable force sleep
    wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
    delay(1);
    return 2;
  }
  else  if (WIFI_STATE == 6)
  {

    //  const char* ssid     = "EVELABS_TECH";
    // const char* password = "BQQJUDWB";
    wifi_fpm_do_wakeup();
    wifi_fpm_close();

    wifi_set_opmode(STATION_MODE);
    wifi_station_connect();
    //  WiFi.setOutputPower(0);
    // WiFi.forceSleepWake();
    //WiFi.mode(WIFI_STA);
    // wifi_station_connect();
    // WiFi.begin(ssid, password);
    //WiFi.begin();
    yield();
    //for (int i = 0; i < 25; i++)
    //{
    while ( WiFi.status() != WL_CONNECTED ) {
      //  delay ( 150 );
      yield() ;


    }//}

    return 2;
  }
}


void configModeCallback (WiFiManager *myWiFiManager) {
   


//  for(i=0;i<1000;i++)
//  {  ESP.wdtFeed();
//

     u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont10_tf);
    u8g2.setCursor(0, 47);
    u8g2.print(myWiFiManager->getConfigPortalSSID());
    u8g2.setCursor(0, 107);
    u8g2.print("prss");
          u8g2.sendBuffer();
//  }



  u8g2.setFont(u8g2_font_crox2h_tr);


}



boolean funct(void)
{
   switch (get_button())
  {
   case 1:  return 1;
     break;

  }
 return NULL;
}
