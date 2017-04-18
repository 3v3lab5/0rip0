String send_req(String Data)
{
  if(Data=="nill")
  {
  return "nill";
  }

  else if(!mqttClient.connected()) 
  {

  }
 else if(Data=="df")
 {
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_req, id);
    mqttClient.publish(pat_channel, "df");
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
 //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
       String medi=_dripo.getMed()+"-"+Data;
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_mon, id);
    mqttClient.publish(pat_channel, chr);
    return "nill";
 } 

    else if(Data=="stop")
 { 
 //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
        String medi=_dripo.getMed()+"-"+Data;
  const char* chr = medi.c_str();
   //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_mon, id);
    mqttClient.publish(pat_channel, chr);
    return "nill";
 } 
}

