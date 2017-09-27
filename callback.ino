/* CallBack fuction MQTT*/

void callback(char* topic, byte* payload, unsigned int length) {

 payload[length] = '\0';
//compare topic of recive msgs

//if topic is drop factor channel create Menu of dropfactor
  if (strcmp((char*)topic, r_channel_df) == 0)
  {
    char *d_f = (char*)payload;
    dpf = MENU ("Dpf", d_f, u8g2);            //create drop factor list
   infuseMenu = 0;                            // move to df menu when list is created


  }

  //if topic is bed channel create Menu of bed

  else if (strcmp(topic, r_channel_pat) == 0)
  {
    char *b_d = (char*)payload;            
    bed = MENU("Bed", b_d, u8g2);          //create bed list
     state = 5;                             // move to bed menu when list is created
  }

    //if topic is Med channel create Menu of Medicne

  else if (strcmp(topic, r_channel_med) == 0)
  {
    char *m_d = (char*)payload;          
    med = MENU("Med", m_d, u8g2);         //create med list
    infuseMenu = 2;                       // move to med menu when list is created
  }


      //if topic is Rate channel create infusion details

  else if (strcmp(topic, r_channel_rate) == 0)
  {
    char *token;
     token = strtok((char*)payload, "&");      // timetable
    _dripo.setTimetable(String((char*)token)); //save  timetable
    token = strtok(NULL, "&");                  // name         
    _dripo.setNam(String((char*)token));        //save patient name
    token = strtok(NULL, "&");                  // Med NAme
    _dripo.setMedName(String((char*)token));    //save med name
    token = strtok(NULL, "&");  // Tvol         //total volume
    _dripo.setTvol(String((char*)token));       //save total vol
    token = strtok(NULL, "&");                  // Rate2set
    _dripo.setR2set(String((char*)token));       //save rate to set
    token = strtok(NULL, "&");                 // Alertml
    _dripo.setAlrt(String((char*)token));        //save alert ml
    infuseMenu = 3;

  }


  //Station Acknowledge is recievd when err an error in infusion is acknowleged by station
  else if (strcmp(topic, r_channel_staAck) == 0)
  {
    char *ack = (char*)payload;
    if(strcmp(ack,"STA_ACK")==0)
    {
staAck=true;                      //ack recieved
    }


  }

  //Version request from server
else if (strcmp(topic, r_channel_version) == 0)
  {
    char *ver = (char*)payload;
        if (strcmp(ver,"ver")==0)
        {
          DataStatus="ver";
        }

  }
}



/*This fucntion is is called every 30s, intilased in setup fn*/

void ticker_handler() {

  ticker_reached = true;       //ticker is true send data.. do nothing otherwise
//boolean sleep = false;


}



