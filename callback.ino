void callback(char* topic, byte* payload, unsigned int length) {

 payload[length] = '\0';

  if (strcmp((char*)topic, r_channel_df) == 0)
  {
    char *d_f = (char*)payload;
    dpf = MENU ("Dpf", d_f, u8g2);
   infuseMenu = 0;


  }
  else if (strcmp(topic, r_channel_pat) == 0)
  {
    char *b_d = (char*)payload;
    bed = MENU("Bed", b_d, u8g2);
     state = 5;
  }
  else if (strcmp(topic, r_channel_med) == 0)
  {
    char *m_d = (char*)payload;
    med = MENU("Med", m_d, u8g2);
    infuseMenu = 2;
  }
  else if (strcmp(topic, r_channel_rate) == 0)
  {
    char *token;
    token = strtok((char*)payload, "&");  // name
    _dripo.setNam(String((char*)token));
    token = strtok(NULL, "&");  // Med NAme
    _dripo.setMedName(String((char*)token));
    token = strtok(NULL, "&");  // Tvol
    _dripo.setTvol(String((char*)token));
    token = strtok(NULL, "&");  // Rate2set
    _dripo.setR2set(String((char*)token));
    token = strtok(NULL, "&");  // Alertml
    _dripo.setAlrt(String((char*)token));
    infuseMenu = 3;

  }
  else if (strcmp(topic, r_channel_staAck) == 0)
  {
    char *ack = (char*)payload;
    if(strcmp(ack,"STA_ACK")==0)
    {
staAck=true;
    }


  }
else if (strcmp(topic, r_channel_version) == 0)
  {
    char *ver = (char*)payload;
        if (strcmp(ver,"ver")==0)
        {
          DataStatus="ver";
        }

  }
}





void ticker_handler() {

  ticker_reached = true;
boolean sleep = false;


}



