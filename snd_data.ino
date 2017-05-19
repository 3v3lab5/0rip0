
#define FPM_SLEEP_MAX_TIME 0xFFFFFFF

void sendRate()
{
  char e_data[50];

  int SRate = _dripo.getRateMl();
  int SIvol = _dripo.getvolInf();
  int SRtime = _dripo.getRtime();
  String medi = _dripo.getMed();
  const char* chr = medi.c_str();
  sprintf(e_data, "%s-%d-%d-%d", chr, SRate, SIvol, SRtime);


 // if (WiFi.status() != WL_CONNECTED)
// {
    //        wifi_fpm_do_wakeup();
    //
    //   wifi_fpm_close();
    //     wifi_station_connect();
    // WiFi.forceSleepWake();
    //
    //  wifi_set_opmode(STATION_MODE);
    //   delay(1);
 //   WiFi.forceSleepWake();
//    delay(1);
 //  wifi_status=6;

// }


  yield() ;
  if (WiFi.status() == WL_CONNECTED) {
    if (mqttClient.connected()) {
    sprintf(rate_channel, mqtt_channel_rate, id);
    mqttClient.publish(rate_channel, e_data);
   // mqttClient.disconnect();
    ticker_reached = false;
  //  wifi_status=5;
   yield() ;
  }
    
  }


}

void Notifier(int err)
{
  char e_data[50];
    String medi = _dripo.getMed();
  const char* chr = medi.c_str();
  sprintf(e_data, "%s-%s", chr, "rate_err");

    if (WiFi.status() == WL_CONNECTED) {
    if (mqttClient.connected()) {
      if(err ==200){
      sprintf(e_data, "%s-%s", chr, "rate_err");

    sprintf(rate_channel,mqtt_channel_err, id);
    mqttClient.publish(rate_channel, e_data);
      }
      if(err ==100){ 
    sprintf(e_data, "%s-%s", chr, "rate_ok");

  sprintf(rate_channel,mqtt_channel_err, id);
    mqttClient.publish(rate_channel, e_data);
        
      }
   // mqttClient.disconnect();
  //  wifi_status=5;
   yield() ;
  }
    
  }
}

