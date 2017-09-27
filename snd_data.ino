/*This funtion sends rate,infused vol, total vol of current infusion to the main station*/


void sendRate()
{
  char e_data[80];                   // all data will merged to this
  int SRate = _dripo.getRateMl();    //get rate in ml
  int SIvol = _dripo.getvolInf();    // get infsed volume
  int Tvol = _dripo.getTvol();       //get total volume
  int SRtime = _dripo.getRtime();    //get remaining time
  String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + "infusing"; //get medicine id,timetable id and status and merged
  const char* chr = medi.c_str();                                          // converted to const char to send via mqtt
  sprintf(e_data, "%s-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol);      // all data is merged
  if (WiFi.status() == WL_CONNECTED) {                                     // check wifi is connection
    if (mqttClient.connected()) {                                          //check mqtt connection
      sprintf(rate_channel, mqtt_channel_mon, id);                           // merge device id with the rate channel to publish data
      mqttClient.publish(rate_channel, e_data, true);                        // publish data to rate channel and data is retained true so that if a new client is
      // mqttClient.disconnect();                                             //conneted it also recieves the last message
      ticker_reached = false;                                                // data is send and ticker is reset
      yield() ;
    }

  }


}



