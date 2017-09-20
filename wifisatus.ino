

int wifi_connect(int WIFI_STATE)
{

  mqttClient.loop();
  const char* DRIPO_NAME = "DRIPO-%d";

  sprintf(id, DRIPO_NAME, ESP.getChipId());


  if (WIFI_STATE == 1)
  {
  //   if (SPIFFS.begin()) {
  //     if (SPIFFS.exists("/config.json")) {
  //       //file exists, reading and loading
  //       File configFile = SPIFFS.open("/config.json", "r");
  //       if (configFile) {
  //         size_t size = configFile.size();
  //         // Allocate a buffer to store contents of the file.
  //         std::unique_ptr<char[]> buf(new char[size]);

  //         configFile.readBytes(buf.get(), size);
  //         DynamicJsonBuffer jsonBuffer;
  //         JsonObject& json = jsonBuffer.parseObject(buf.get());
  //         if (json.success()) {

  //       //  strcpy(mqtt_server, json["mqtt_server"]);

  //         } else {
  //           //   Serial.println("failed to load json config");
  //         }
  //       }
  //     }
  //   } else {
  //     //Serial.println("failed to mount FS");
  //   }

    // WiFiManager wifiManager;
    // //  wifiManager.setSaveConfigCallback(saveConfigCallback);
    // wifiManager.setConnectTimeout(10);
    // wifiManager.setConfigPortalTimeout(1);


    // if (!wifiManager.autoConnect(id)) {

 WiFi.mode(WIFI_STA);    //   return 2;
 WiFi.begin();
 yield();
    // }

    // if ( WiFi.status() == WL_CONNECTED ) {
    //   mqtt_reconnect();
    // }
    return 2;

  }
  else if (WIFI_STATE == 2)
  {
    // ESP.wdtFeed();

    if ( WiFi.status() == WL_CONNECTED ) {
      if (!mqttClient.connected()) {
        long now = millis();
        if (now - lastReconnectAttempt > 5000 && connection < 4) {
          lastReconnectAttempt = now;
           connection++;

          // Attempt to reconnect
          if (mqtt_reconnect()) {
            lastReconnectAttempt = 0;
            connection=0;
          }

        }
      }

    }
    //
    //              if(sleep==false)
    //          {
    //      //
    //    wifi_set_sleep_type(MODEM_SLEEP_T);
    //           wifi_fpm_open();
    //           wifi_fpm_do_sleep(16843455);
    //           yield();
    //        //  wifi_fpm_do_sleep(26843455);
    //      //    delay(500);
    //          sleep = true;
    //     }
    //    return 2;
    return 2;
  }



  else if (WIFI_STATE == 4) {
  //  WiFi.mode(WIFI_OFF);
   WiFi.mode(WIFI_AP);
   // delay(500);
    WiFiManager wifiManager;
   // wifiManager.startConfigPortal("OnDemandAP");
   
//       WiFi.mode(WIFI_OFF);

//   //WiFi.mode(WIFI_STA);
//           yield();
  //  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
     WiFiManager wifiManager_Ondemand;
   wifiManager_Ondemand.setBreakAfterConfig(true);

//    //wifiManager_Ondemand.setConfigPortalTimeout(150);
 //    wifiManager_Ondemand.addParameter(&custom_mqtt_server);
     wifiManager_Ondemand.setConfigPortalExitable(funct);
//       //  ESP.wdtFeed();
//         yield();
//     WiFi.mode(WIFI_OFF);
//     WiFi.mode(WIFI_AP);
//     delay(500);
     if (!wifiManager_Ondemand.startConfigPortal(id)) {
//       //      Serial.println("failed to connect and hit timeout");
//       //      delay(3000);
//       //      //reset and try again, or maybe put it to deep sleep
//       //      ESP.reset();
//       //      delay(5000);
//       WiFi.mode(WIFI_OFF);
//             delay(3000);


    }
// //yield();

    //mqtt_server = custom_mqtt_server.getValue();
 //strcpy(mqtt_server, custom_mqtt_server.getValue());


    // Serial.println("saving config");
    // DynamicJsonBuffer jsonBuffer;
    // JsonObject& json = jsonBuffer.createObject();
    // json["mqtt_server"] = mqtt_server;

    // File configFile = SPIFFS.open("/config.json", "w");
    // if (!configFile) {
    //   //    Serial.println("failed to open config file for writing");
    // }

    // //  json.printTo(Serial);
    // json.printTo(configFile);
    // configFile.close();
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

}









boolean funct(void)
{
  ESP.wdtFeed();
  u8g2.clearBuffer();
  u8g2.setFont( u8g2_font_crox1h_tr);
  u8g2.setCursor(2, 20);
  u8g2.print("Hotspot");
  u8g2.setCursor(32, 30);
  u8g2.print("Active");
  //  u8g2.drawXBM( 9, 50,hotspot_width, hotspot_height, hotspot_bits);
  u8g2.drawDisc(32, 67, 4, U8G2_DRAW_ALL);
  dialogbox1.dialog_box("Cancel&", 108, 1);

  hotspot.hotspot();
  hotspot1.hotspot();
  hotspot2.hotspot();

  u8g2.sendBuffer();
  u8g2.setFont(u8g2_font_crox2h_tr);
  switch (get_button())
  {
    case 1:  return 1;
      break;

  }
  return NULL;
}
