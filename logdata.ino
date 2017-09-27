/*For testing and preclincal trials only. Log each drop and details */

int LogData(unsigned long int _ElTime, int stats)
{
  if (stats == 1)
  {
    char e_data[80];                            // all data will merged to this
    int SRate = _dripo.getRateMl();              //get rate in ml
    int SIvol = _dripo.getvolInf();             // get infsed volume
    int S_df = _dripo.getDf();                  // get drop factor

    String medi = _dripo.getMed() + "-" + _dripo.getTimetable();   //get medicine id,timetable id
    long _DropCount = _dripo.getDcount();                          //get drop count
    const char* chr = medi.c_str();

    sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, S_df, _DropCount, _ElTime, SRate, SIvol);    //all data is merged
    if (WiFi.status() == WL_CONNECTED) {                                                   // check wifi connection
      if (mqttClient.connected()) {                                                        //check mqtt connection
        sprintf(log_channel, mqtt_channel_log, id);                                        //merge device id with publish channel
        mqttClient.publish(log_channel, e_data);                                           //publish data
      }
    }

    return 0;
  }

  else {
    return 0;
  }
}
