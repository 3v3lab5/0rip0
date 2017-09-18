int LogData(unsigned long int _ElTime, int stats)
{
  if(stats==1)
  {
    char e_data[80];
  int SRate = _dripo.getRateMl();
  int SIvol = _dripo.getvolInf();
  int S_df = _dripo.getDf();

  String medi = _dripo.getMed();
  long _DropCount = _dripo.getDcount();
  const char* chr = medi.c_str();

    sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, S_df, _DropCount, _ElTime, SRate, SIvol);
    if (WiFi.status() == WL_CONNECTED) {
      if (mqttClient.connected()) {
        sprintf(log_channel, mqtt_channel_log, id);
        mqttClient.publish(log_channel, e_data);
      }
    }

   return 0;
  }

  else{
    return 0;
  }
}
