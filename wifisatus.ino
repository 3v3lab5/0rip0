

int wifi_connect(int WIFI_STATE)
{
  mqttClient.loop();

  const char* DRIPO_NAME = "DRIPO-%d";

  sprintf(id, DRIPO_NAME, ESP.getChipId());


  if (WIFI_STATE == 1)
  {
    if ( WiFi.status() != WL_CONNECTED )
    {
      WiFiManager wifiManager;
      //  wifiManager.setSaveConfigCallback(saveConfigCallback);
      wifiManager.setConnectTimeout(10);
      wifiManager.setConfigPortalTimeout(1);


      if (!wifiManager.autoConnect(id)) {

        // WiFi.mode(WIFI_STA);

        return 2;
        // WiFi.begin();
        // yield();
      }
    }
    if ( WiFi.status() == WL_CONNECTED && strcmp(mqtt_server, "0") != 0 ) {
      if (!mqttClient.connected()) {
        mqtt_reconnect();
      }
    }


    return 2;

  }
  else if (WIFI_STATE == 2)
  {
    // ESP.wdtFeed();

    if ( WiFi.status() == WL_CONNECTED && strcmp(mqtt_server, "0") != 0) {
      if (!mqttClient.connected()) {
        long now = millis();
        if (now - lastReconnectAttempt > 5000 && connection < 2) {
          lastReconnectAttempt = now;
          connection++;

          // Attempt to reconnect
          if (mqtt_reconnect()) {
            lastReconnectAttempt = 0;
            connection = 0;
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
    WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    WiFiManager wifiManager_Ondemand;
    wifiManager_Ondemand.setBreakAfterConfig(true);

    //    //wifiManager_Ondemand.setConfigPortalTimeout(150);
    wifiManager_Ondemand.addParameter(&custom_mqtt_server);
    wifiManager_Ondemand.setConfigPortalExitable(funct);
    //       //  ESP.wdtFeed();
    //         yield();
    //     WiFi.mode(WIFI_OFF);
    //     WiFi.mode(WIFI_AP);
    //     delay(500);
    if (mqttClient.connected()) {
      mqttClient.disconnect();

    }
    if (!wifiManager_Ondemand.startConfigPortal(id)) {
      //       //      Serial.println("failed to connect and hit timeout");
      //       //      delay(3000);
      //       //      //reset and try again, or maybe put it to deep sleep
      //       //      ESP.reset();
      //       //      delay(5000);
      //       WiFi.mode(WIFI_OFF);
      //             delay(3000);


    }

    strcpy(mqtt_server, custom_mqtt_server.getValue());

    Serial.println(mqtt_server);

    EEPROM.begin(512);
    EEPROM.put(0, mqtt_server);
    EEPROM.commit();
    EEPROM.end();
    lastReconnectAttempt = 0;
    connection = 1;

    state = 1;
    ui_state = 1;

    return 1;
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
