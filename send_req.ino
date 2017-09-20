String send_req(String Data)
{
  if(Data=="nill")
  {
  return "nill";
  }

  else if(!mqttClient.connected()) 
  {
  return "nill";

  }
 else if(Data=="df")
 {
     char e_data[50];
  String medi=_dripo.getMed();
  const char* chr = medi.c_str();
     sprintf(e_data, "%s", chr);
    sprintf(pat_channel, mqtt_channel_req, id);
    mqttClient.publish(pat_channel,chr);
    return "nill";
 }

  else if(Data=="bed")
 {
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_bedreq, id);
    mqttClient.publish(pat_channel, "bed");
    return "nill";
 }
  else if(Data=="med")
 {
   String medi=_dripo.getBed();
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_medreq, id);
    mqttClient.publish(pat_channel, chr);
    return "nill";
 }
   else if(Data=="rate")
 { 
   //String medi=_dripo.getBed()+"-"+_dripo.getMed();
      String medi=_dripo.getMed();
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_ratereq, id);
    mqttClient.publish(pat_channel, chr);
    return "nill";
 } 

    else if(Data=="start")
 { 

    char e_data[80];

  int SRate = _dripo.getRateMl();
  int SIvol = _dripo.getvolInf();
  int SRtime = _dripo.getRtime();
   int Tvol = _dripo.getTvol();
  int S_df = _dripo.getDf();

 //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
        String medi=_dripo.getMed()+"-"+_dripo.getTimetable()+"-"+Data;
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
     sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime,Tvol,S_df);
    sprintf(pat_channel, mqtt_channel_mon, id);
    
    mqttClient.publish(pat_channel,e_data,true);
    return "nill";
 } 


  else if(Data=="stop")
 { 
      char e_data[80];

  int SRate = _dripo.getRateMl();
  int SIvol = _dripo.getvolInf();
  int SRtime = _dripo.getRtime();
   int Tvol = _dripo.getTvol();
  int S_df = _dripo.getDf();

 //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
        String medi=_dripo.getMed()+"-"+_dripo.getTimetable()+"-"+Data;
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
        sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime,Tvol,S_df);
    sprintf(pat_channel, mqtt_channel_mon, id);
    mqttClient.publish(pat_channel, e_data,true);
    return "nill";
 }

//    else if(Data=="dev_ack")
//    {
// String ack=_dripo.getMed()+"-"+Data;
//   const char* chr = ack.c_str();
//    sprintf(staAck_channel, mqtt_channel_devack, id);
//    mqttClient.publish(staAck_channel, chr,true);
// return "nill";
//    }

    else if(Data=="ver")
 { 
    sprintf(version_channel,mqtt_channel_myversion, id);
    mqttClient.publish(version_channel,VERSION);
    return "nill";
 }
 
}

