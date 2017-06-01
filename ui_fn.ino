void UI_Logo() {


  u8g2.setFont( u8g2_font_profont22_tf );
  u8g2.setCursor(4, 64);
  u8g2.print("Dripo");


}


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
void UI_Menu()

{
  u8g2.setFont(u8g2_font_crox2h_tr);

  //u8g2 = U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI (U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10);
  analogWrite(IR_PIN, 0);

  u8g2.drawXBM(8 - ui_x, 35, ic_opacity_black_24dp_width, ic_opacity_black_24dp_height, ic_opacity_black_24dp_bits);
  u8g2.setCursor(6 - ui_x, 100);
  u8g2.print("INFUSE");

  u8g2.drawXBM(72 - ui_x, 35, ic_settings_black_24dp_width, ic_settings_black_24dp_height, ic_settings_black_24dp_bits);
  u8g2.setCursor(73 - ui_x, 100);
  u8g2.print("SETUP");

  u8g2.drawXBM(136 - ui_x, 35, ic_power_settings_new_black_24dp_width, ic_power_settings_new_black_24dp_height, ic_power_settings_new_black_24dp_bits);
  u8g2.setCursor(138 - ui_x, 100);
  u8g2.print("SLEEP");
  u8g2.drawCircle(18, 120, 3, U8G2_DRAW_ALL);
  u8g2.drawCircle(32, 120, 3, U8G2_DRAW_ALL);
  u8g2.drawCircle(46, 120, 3, U8G2_DRAW_ALL);
  u8g2.drawDisc(18 + dot_x, 120, 3, U8G2_DRAW_ALL);

}

void UI_Rate()

{
  analogWrite(IR_PIN, 512);
  u8g2.setDrawColor(1);
  String txt;
  txt = _dripo.getRateMl();
  u8g2.setFont(u8g2_font_timR24_tn);
  u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 47);
  u8g2.print(_dripo.getRateMl());
  u8g2.drawHLine(0, 64, 13);
  u8g2.drawHLine(51, 64, 13);
  u8g2.setDrawColor(2);
  u8g2.drawBox(13, 57, 38, 15);
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(19, 68);
  u8g2.print("ml/hr");
  u8g2.setDrawColor(1);

  if (MonState == 0) {
    u8g2.setCursor(0, 92);
    u8g2.print("Rate to set");
    u8g2.setCursor(34, 128);
    u8g2.print("ml/hr");
    u8g2.setFont(u8g2_font_timR18_tn);
    u8g2.setCursor(0, 116);
    u8g2.print(_dripo.getrate2set());
  }
  else if (MonState == 1) {
    u8g2.setCursor(8, 92);
    u8g2.print("Cancel?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }
  else if (MonState == 2) {
    u8g2.setCursor(5, 92);
    u8g2.print("Monitor?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }

  else if (MonState == 3) {

    u8g2.setCursor(0, 92);
    u8g2.print("Vol infusd");
    u8g2.setCursor(36, 128);
    u8g2.print("ml");
    u8g2.setFont(u8g2_font_timR18_tn);
    u8g2.setCursor(0, 116);
    u8g2.print(_dripo.getvolInf());
 
int alt = _dripo.Alert(timeElapsed);

if( alt != NO_ERR)
{
  sendAlert(alt);
}
  
 else if (ticker_reached) {

      sendRate();
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
          state = 2;
          ui_state = 2;
        }
        else {
          _dripo.setDf(dpf.getSelect());
          DataStatus = "bed";
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
          infuseMenu = 0;
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
          DataStatus = "rate";

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
          infuseMenu = 2;

        }
        else if (dialogbox.getDia() == "Yes") {
          if (stateOfCharge > (15 + (_dripo.getTtime() / 12)))
          {
            ui_state = 3;
            state = 9;
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

void UI_Update() {

  u8g2.setDrawColor(1);

  u8g2.drawXBM(8, 35, update_icon_width, update_icon_height, update_icon_bits);
  u8g2.setCursor(2, 100);
  u8g2.print("Updating");



}


void UI_Shutdown()
{ u8g2.setDrawColor(1);

  u8g2.setCursor(2, 62);
  u8g2.print("Shutdown");
  dialogbox.dialog_box("No&Yes&", 72, 2);
}

void UI_Setup()
{
  //U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10);

  Setup.display_menu();

}

void UI_WifiConf()
{
  u8g2.setCursor(1, 62);
  u8g2.print("Config Wifi");
  dialogbox.dialog_box("No&Yes&", 72, 2);

}

void UI_fin()
{

  dialogbox.dialog_box("Ok&", 82, 1);

}

void UI_dripo()
{
  // u8g2=U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI (U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ U8X8_PIN_NONE);

  u8g2.setFont(u8g2_font_profont10_tf);

  const char* DRIPO_NAME = "DRIPO-%d";


  sprintf(id, DRIPO_NAME, ESP.getChipId());
  u8g2.setCursor(0, 20);
  u8g2.print(id);
  u8g2.setCursor(0, 40);
  u8g2.print(analogRead(A0));
  u8g2.setCursor(0, 70);
  u8g2.print(stateOfCharge);
  u8g2.setCursor(0, 100);
  u8g2.print(cellVoltage);
  u8g2.setCursor(0, 120);
  //    u8g2.print(pot);


  u8g2.setFont(u8g2_font_crox2h_tr);


}


void UI_ServErr()
{
  u8g2.setCursor(32 - (u8g2.getStrWidth("connection") / 2), 42);
  u8g2.print("connection");
  u8g2.setCursor(32 - (u8g2.getStrWidth("error") / 2), 62);
  u8g2.print("error");
  dialogbox.dialog_box("Ok&", 72, 1);

}
void UI_batlow()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(4, 64);
  u8g2.print("Batlow");
}
void UI_InfBatChK()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(4, 64);
  u8g2.print("lowbat");
  dialogbox1.dialog_box("Ok&", 72, 1);

}
void UI_batchk()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(4, 64);
  u8g2.print("Batlow");

}
void UI_batfull()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(4, 64);
  u8g2.print("BatFull");

}
