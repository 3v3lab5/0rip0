/*Function reconnect the connection wit mosquitto and initilzes the subscribe channnel with QOS*/

boolean mqtt_reconnect() {

  mqttClient.setServer(mqtt_server, mqtt_port);         //mosquitto server and port is initilized
  mqttClient.setCallback(callback);                     // callback fuction for mosquitto is initilzed. this fuction is called when a message is recieved
  if (mqttClient.connect(id)) {                         // connect to mosqutto server and checks the connection
    yield();
    // sprintf(up_channel, mqtt_channel_update, id);
    // mqttClient.subscribe(up_channel);
    mqttClient.publish("active", id);                  // publishes the device id to chennel active

    //create subscrbe channels
    sprintf(r_channel_df, mqtt_channel_df, id);        
    sprintf(r_channel_pat, mqtt_channel_pat, id);
    sprintf(r_channel_version, mqtt_channel_version, id);
    sprintf(r_channel_update, mqtt_channel_update, id);
    sprintf(r_channel_med, mqtt_channel_med, id);
    sprintf(r_channel_rate, mqtt_channel_r2set, id);
    sprintf(r_channel_staAck, mqtt_channel_staAck, id);


    //subscribe to channels
    mqttClient.subscribe(r_channel_pat, qos);
    mqttClient.subscribe(r_channel_version, qos);
    mqttClient.subscribe(r_channel_update, qos);
    mqttClient.subscribe(r_channel_df, qos);
    mqttClient.subscribe(r_channel_med, qos);
    mqttClient.subscribe(r_channel_rate, qos);
    mqttClient.subscribe(r_channel_staAck, qos);
  }
  return mqttClient.connected();
}
