boolean mqtt_reconnect() {
mqttClient.setServer(mqtt_server, mqtt_port);
mqttClient.setCallback(callback);
  if (mqttClient.connect(id)) {
    // sprintf(up_channel, mqtt_channel_update, id);
    // mqttClient.subscribe(up_channel);
    mqttClient.publish("active", id);
    sprintf(r_channel_df, mqtt_channel_df, id);
    sprintf(r_channel_pat, mqtt_channel_pat, id);
    sprintf(r_channel_version, mqtt_channel_version, id);
    sprintf(r_channel_update, mqtt_channel_update, id);
    mqttClient.subscribe(r_channel_pat,qos);
    mqttClient.subscribe(r_channel_version,qos);
    mqttClient.subscribe(r_channel_update,qos);
    mqttClient.subscribe(r_channel_df,qos);
    sprintf(r_channel_med, mqtt_channel_med, id);
    mqttClient.subscribe(r_channel_med,qos);
    sprintf(r_channel_rate, mqtt_channel_r2set, id);
    mqttClient.subscribe(r_channel_rate,qos);
    sprintf(r_channel_staAck, mqtt_channel_staAck, id);
    mqttClient.subscribe(r_channel_staAck,qos);
  }
  return mqttClient.connected();
}
