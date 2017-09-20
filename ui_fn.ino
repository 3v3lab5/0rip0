//File contains most of the UI fns 
//Print Dev name on screen
void UI_Logo() {


  u8g2.setFont( u8g2_font_profont22_tf );
  u8g2.setCursor(4, 64);
  u8g2.print("Dripo");


}

//connecting to wifi network
void UI_Wifi()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(-1.5, 27);
  u8g2.print("connecting");
  u8g2.setCursor(8, 47);
  u8g2.print("to Wi-Fi");
  u8g2.setCursor(7, 67);
  u8g2.print("network");
  u8g2.drawXBM( 20, 85, wifi_01_width, wifi_01_height, wifi_01_bits);

}

//MAin Menu
void UI_Menu()

{

  Menu.displayc();

}


//Rate Menu-- contains monitoring mode also
void UI_Rate()

{
  analogWriteFreq(38000);           ///set ir frequency to 38khz
  analogWrite(IR_PIN,irAmp);        // Start Ir
  logstatus=LogData(logtime,logstatus);      //log data on each drop

  u8g2.setDrawColor(1);
  String txt;
  txt = _dripo.getRate();
  u8g2.setFont(u8g2_font_timR24_tn);
  u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 47);
  u8g2.print(_dripo.getRate());
 // u8g2.drawHLine(0, 64, 13);
 // u8g2.drawHLine(51, 64, 13);
  u8g2.setDrawColor(detect1);                   // change to 0 when detects otherwise 2
  u8g2.drawBox(13, 57, 38, 15);
  u8g2.setDrawColor(detect2);                   //change to 1 when detects  otherwise 0
  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(19, 68);
  u8g2.print("dpm");
  u8g2.setDrawColor(1);
 if(detect1==0&&detect2==1)      //for drop notification .the dpm icons blinks in each drop
  {
            long detecttime = millis();
            if(detecttime-lastDAttempt>200)
            {
                   detect1=2;
                    detect2=0;
                lastDAttempt=0;
            }

  }


//first state shows the rate to set in screen// idle time is made 0 to disable powersave mode
  if (MonState == 0) {
      idle_time = 0;      //disable powersave mode
    u8g2.setCursor(0, 92);
    u8g2.print("Rate to set");
    u8g2.setCursor(34, 126);
    u8g2.print("dpm");
    u8g2.setFont(u8g2_font_timR18_tn);
    u8g2.setCursor(0, 116);
    u8g2.print(_dripo.getR2setDPM());

  }

  // canceling infusion
  else if (MonState == 1) {
    u8g2.setCursor(8, 92);
    u8g2.print("Cancel?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }

  //Ask for move to monitring state or not
  else if (MonState == 2) {
    u8g2.setCursor(5, 92);
    u8g2.print("Monitor?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }
//monitoring state
  else if (MonState == 3) {
  altmsg = _dripo.Alert(timeElapsed);    //alert msg is created using the time elapsed btween drops

 if(altmsg==NO_ERR||devAck==true)
 {  

   if(altmsg==NO_ERR)
   {
        devAck=false;
      staAck=false;
 
     if (ticker_reached) {

      sendRate();
    }     
   }

   _errAlert.wasExecuted();
    u8g2.setCursor(0, 92);
    u8g2.print("Vol infused");
    u8g2.setCursor(36, 128);
    u8g2.print("ml");
    u8g2.setFont(u8g2_font_timR18_tn);
    u8g2.setCursor(0, 116);
    u8g2.print(_dripo.getvolInf());

 }
// else if(devAck==true)
//  {
//   _errAlert.wasExecuted();
//    u8g2.setCursor(0, 92);
//    u8g2.print("Vol infused");
//    u8g2.setCursor(36, 128);
//    u8g2.print("ml");
//    u8g2.setFont(u8g2_font_timR18_tn);
//    u8g2.setCursor(0, 116);
//    u8g2.print(_dripo.getvolInf());
//  }
  else if(altmsg!=NO_ERR)
  {
  if(staAck==true)
  { 
    acktime= millis();
    if(acktime>60000)
    {
      staAck=false;
      acktime=0;
   _errAlert.wasExecuted();
    }
  }
  sleeper=_errAlert.display_err(_dripo.getTimetable(),altmsg,devAck,staAck,id,_dripo.getMed(),_dripo.getRateMl(),_dripo.getvolInf(),_dripo.getRtime(),_dripo.getTvol());
  // if(callerrhandlerflag==true)
  // {
  //     sleeper=_errAlert.display_err(altmsg,devAck,staAck,id,_dripo.getMed());
  //     callerrhandlerflag=false;

  // }
   switch (get_button())

    {
      case 1: devAck=true;
  sleeper=_errAlert.display_err(_dripo.getTimetable(),altmsg,devAck,staAck,id,_dripo.getMed(),_dripo.getRateMl(),_dripo.getvolInf(),_dripo.getRtime(),_dripo.getTvol());

        PMonState=MonState;
	      MonState = 0;
		
        break;

    }
  
 }

  

   
  }
}

void UI_infuse()

{
  if (infuseMenu == 0)
  {
    dpf.display_menu();
    switch (get_button())
    {
      case 1: if (dpf.getSelect() == "<<back") {
        infuseMenu = 2;
        }
        else {
          _dripo.setDf(dpf.getSelect());
          DataStatus = "rate";
          //  infuseMenu = 1;
        }
        break;
      case 3: dpf.up();
        break;
      case 4: dpf.dwn();
        break;
    }
  }

  if (infuseMenu == 1)
  {
    bed.display_menu();
    switch (get_button())
    {
      case 1: if (bed.getSelect() == "<<back")
        {
          state = 2;
          ui_state = 2;
        }
        else {
          _dripo.setBed(bed.getSelect());
          DataStatus = "med";
          //    infuseMenu = 2;
          //  ui_state = 3;

          //  state = 9;
        }
        break;
      case 3: bed.up();
        break;
      case 4: bed.dwn();
        break;
    }
  }

  if (infuseMenu == 2)
  {
    med.display_menu();
    switch (get_button())
    {
      case 1: if (med.getSelect() == "<<back")
        {
          infuseMenu = 1;
        }
        else {
          _dripo.setMed(med.getSelect());
          DataStatus = "df";

          //        infuseMenu = 3;

          //   ui_state = 3;

          //   state = 9;
        }
        break;
      case 3: med.up();
        break;
      case 4: med.dwn();
        break;
    }
  }


  if (infuseMenu == 3)
  {
    String txt;
    txt = _dripo.getName();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 30);
    u8g2.print(_dripo.getName());
    txt = _dripo.getMedName();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 50);
    u8g2.print(_dripo.getMedName());
    txt = _dripo.getTvol();
    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 70);
    u8g2.print(_dripo.getTvol());
    txt = _dripo.getDf();
    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 90);
    u8g2.print(_dripo.getDf());
    u8g2.setCursor(36, 70);
    u8g2.print("ml");
    u8g2.setCursor(36, 90);
    u8g2.print("dpf");

    dialogbox.dialog_box("No&Yes&", 102, 2);

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          infuseMenu = 0;

        }
        else if (dialogbox.getDia() == "Yes") {
          if (stateOfCharge > (15 + (_dripo.getTtime() / 12)))
          {
            ui_state = 16;
            state = 18;
          }
          else
          {

            ui_state = 13;
            state = 16;
          }

        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }
}

///Update UI....will be removed
void UI_Update() {

  u8g2.setDrawColor(1);

  u8g2.drawXBM(8, 35, update_icon_width, update_icon_height, update_icon_bits);
  u8g2.setCursor(2, 100);
  u8g2.print("Updating");



}

//Shutdown dialog box
void UI_Shutdown()
{ u8g2.setDrawColor(1);

  u8g2.setCursor(32 - (u8g2.getStrWidth("Sleep") / 2), 62);
  u8g2.print("Sleep");
  dialogbox.dialog_box("No&Yes&", 72, 2);
}


//Setup MEnu
void UI_Setup()
{
  //U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10);

  Setup.display_menu();
  analogWrite(IR_PIN,0);

}

//shows tis UI when data is requestd and wifi is not connected
void UI_WifiConf()
{
  u8g2.setCursor(1, 62);
  u8g2.print("Config Wifi");
  dialogbox.dialog_box("No&Yes&", 72, 2);

}

//UI
void UI_fin()
{

  dialogbox.dialog_box("Ok&", 82, 1);

}


//just a device Menu to know the status of device.. need updation
void UI_dripo()
{
    //digitalWrite(BUZZ_PIN, HIGH);
//tone(BUZZ_PIN,1000,700);
    analogWriteFreq(38000);
  analogWrite(IR_PIN,irAmp);
  // u8g2=U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI (U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ U8X8_PIN_NONE);
//  Wire.beginTransmission(0x20); // transmit to device #20 (0x20)
//  Wire.write(0x30);// sends instruction byte
//  Wire.write(0x03);
// Wire.endTransmission();
//
//    Wire.requestFrom(0x20, 2);
//  byte MSB = Wire.read();
//byte LSB = Wire.read();

if(analogRead(A0)<512)
{
  irAmp=irAmp+5;
}

if(analogRead(A0)>530)
{
  irAmp=irAmp-5;
}

  u8g2.setFont(u8g2_font_profont10_tf);

  const char* DRIPO_NAME = "DRIPO-%d";


  sprintf(id, DRIPO_NAME, ESP.getChipId());
  u8g2.setCursor(0, 20);
  u8g2.print(id);
  u8g2.setCursor(0, 40);
  u8g2.print(analogRead(A0));
    u8g2.setCursor(32, 40);
  //u8g2.print(bigNum);
  u8g2.setCursor(0, 70);
  u8g2.print( batteryMonitor.getSoC());
  u8g2.setCursor(0, 100);
  u8g2.print(cellVoltage);
  u8g2.setCursor(0, 120);
    u8g2.print(VERSION);


  u8g2.setFont(u8g2_font_crox2h_tr);


}

//show server err if data is requestd and Mosquitto is not connected

void UI_ServErr()
{
  u8g2.setCursor(32 - (u8g2.getStrWidth("connection") / 2), 42);
  u8g2.print("connection");
  u8g2.setCursor(32 - (u8g2.getStrWidth("error") / 2), 62);
  u8g2.print("error");
  dialogbox.dialog_box("Ok&", 72, 1);

}
//Bat LOW
void UI_batlow()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35,batlow_width,batlow_height,batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW")/ 2), 100);
  u8g2.print("BAT LOW");
}

//BAttery Check Before starting Infusion as warning to show the battey level is insfficent for the insfusion
void UI_InfBatChK() 
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 30,batlow_width,batlow_height,batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW")/ 2), 90);
  u8g2.print("BAT LOW");
  dialogbox1.dialog_box("Ok&", 100, 1);

}

//BAttery LOW UI
void UI_batchk()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35,batlow_width,batlow_height,batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW")/ 2), 100);
  u8g2.print("BAT LOW");

}

//Battey Full UI
void UI_batfull()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35,batfull_width,batfull_height,batfull_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT FULL")/ 2), 100);
  u8g2.print("BAT FULL");
}

//void Off_Infuse()
//{
//  if (infuseMenu == 1)
//  {
//    Off_dpf.display_menu();
//    switch (get_button())
//    {
//      case 1: if (dpf.getSelect() == "<<back") {
//infuseMenu = 0;
//        }
//        else {
//          _dripo.setDf(Off_dpf.getSelect());
//
//        }
//        break;
//      case 3: dpf.up();
//        break;
//      case 4: dpf.dwn();
//        break;
//    }
//  }
//
//  if (infuseMenu == 0)
//  {
//    switch (get_button())
//    {
//      case 1: if (bed.getSelect() == "<<back")
//        {
//          state = 2;
//          ui_state = 2;
//        }
//        else {
//          _dripo.setBed(bed.getSelect());
//          DataStatus = "med";
//          //    infuseMenu = 2;
//          //  ui_state = 3;
//
//          //  state = 9;
//        }
//        break;
//      case 3: bed.up();
//        break;
//      case 4: bed.dwn();
//        break;
//    }
//  }
//
//  if (infuseMenu == 2)
//  {
//    med.display_menu();
//    switch (get_button())
//    {
//      case 1: if (med.getSelect() == "<<back")
//        {
//          infuseMenu = 1;
//        }
//        else {
//          _dripo.setMed(med.getSelect());
//          DataStatus = "df";
//
//          //        infuseMenu = 3;
//
//          //   ui_state = 3;
//
//          //   state = 9;
//        }
//        break;
//      case 3: med.up();
//        break;
//      case 4: med.dwn();
//        break;
//    }
//  }
//
//
//  if (infuseMenu == 3)
//  {
//    String txt;
//    txt = _dripo.getName();
//    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 30);
//    u8g2.print(_dripo.getName());
//    txt = _dripo.getMedName();
//    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 50);
//    u8g2.print(_dripo.getMedName());
//    txt = _dripo.getTvol();
//    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 70);
//    u8g2.print(_dripo.getTvol());
//    txt = _dripo.getDf();
//    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 90);
//    u8g2.print(_dripo.getDf());
//    u8g2.setCursor(36, 70);
//    u8g2.print("ml");
//    u8g2.setCursor(36, 90);
//    u8g2.print("dpf");
//
//    dialogbox.dialog_box("No&Yes&", 102, 2);
//
//    switch (get_button())
//    {
//      case 1: if (dialogbox.getDia() == "No") {
//          infuseMenu = 0;
//
//        }
//        else if (dialogbox.getDia() == "Yes") {
//          if (stateOfCharge > (15 + (_dripo.getTtime() / 12)))
//          {
//            ui_state = 16;
//            state = 18;
//          }
//          else
//          {
//
//            ui_state = 13;
//            state = 16;
//          }
//
//        }
//        break;
//      case 3: dialogbox._diaup();
//        break;
//      case 4: dialogbox._diadwn();
//        break;
//    }
//  }
//}
//calibration screen.. loading animation
void UI_Calib()
{

load.draw();

}
