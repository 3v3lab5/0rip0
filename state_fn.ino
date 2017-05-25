void drawLogo()
{
  if (logo_time > 1500)
  {
    state = 1;
    ui_state = 1;
  }
}

void wifi_init()
{
  wifi_status = 1;
  state = 2;
  ui_state = 2;

}

void menu_1()
{
  dot_x = 0;
  if (ui_x > 0)
  {
    ui_x = ui_x - 32;


  }
  switch (get_button())
  {
    case 3:  state = 3;
      break;
    case 1 : //WiFi.forceSleepWake();
      if (WiFi.status() == WL_CONNECTED)
      { if (mqttClient.connected()) {
          DataStatus = "df";
          //           state = 5;

        }
        else {
          state = 14;
          ui_state = 11;
        }
      }

      else {
        state = 10;
        ui_state = 8;
      }

      break;

  }
}

void menu_2()
{

  dot_x = 14;

  if (ui_x < 64)
  {
    ui_x = ui_x + 32;


  }
  if (ui_x > 64)
  {
    ui_x = ui_x - 32;


  }
  switch (get_button())
  {
    case 3:  state = 4;
      break;
    case 4:    state = 2;
      break;
    case 1 :  state = 6;
      ui_state = 7;

      break;
  }



}

void menu_3()
{
  dot_x = 28;

  if (ui_x < 128)
  {
    ui_x = ui_x + 32;

  }
  switch (get_button())
  {
    case 4:  state = 3;
      break;
    case 1 :  state = 7;
      ui_state = 6;

      break;
  }

}

void M_infuse()
{
  if (DataStatus == "nill")
  {
    ui_state = 4;

  }


}

void M_setup()
{
  switch (get_button())
  {
    case 1: if (Setup.getSelect() == "<<back")
      {
        state = 3;
        ui_state = 2;
      }
      else  if (Setup.getSelect() == "wifi conf") {
        state = 3;
        ui_state = 2;
        wifi_status = 4;
      }
      else  if (Setup.getSelect() == "update") {
        if (WiFi.status() == WL_CONNECTED)
        {

          ui_state = 5;
          state = 8;
        }
      }
      else  if (Setup.getSelect() == "system") {
        ui_state = 10;
        state = 13;
      }
      break;
    case 3: Setup.up();
      break;
    case 4: Setup.dwn();
      break;
  }
}
void M_pwroff()
{
  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "No") {
        state = 4;
        ui_state = 2;

      }
      else if (dialogbox.getDia() == "Yes") {

        u8g2.setPowerSave(1);
        system_deep_sleep_set_option(2);
        system_deep_sleep(0);
        //        yield();
        delay(500);
      }
      break;
    case 3: dialogbox._diaup();
      break;
    case 4: dialogbox._diadwn();
      break;
  }
}

void update_dripo()
{
  //  if(WiFi.status() != WL_CONNECTED) {
  //
  //  wifi_fpm_do_wakeup();
  //  wifi_fpm_close();
  //   delay(5000);
  //
  //  }
  ESPhttpUpdate.update("http://evelabs.co/Drip0.ino.nodemcu.bin");

}

void Sho_Rate()
{
  if (_dripo.MonRate() == 1 && MonState == 0)
  {
    PMonState = MonState;
    MonState = 2;
  }


  if (MonState == 0 || MonState == 3) {


    switch (get_button())

    {
      case 1:  PMonState = MonState;
        MonState = 1;
        break;

    }


  }


  else if (MonState == 2) {

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          MonState = PMonState;
        }
        else if (dialogbox.getDia() == "Yes") {
          MonState = 3;
          DataStatus = "start";
        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }

  else if (MonState == 1) {

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          MonState = PMonState;
        }
        else if (dialogbox.getDia() == "Yes") {
          // dpf->~MENU();
          // delete dpf;
          //MENU *dpf= new MENU;
          if (PMonState == 3)
          {
            DataStatus = "stop";
          }
          state = 2;
          ui_state = 2;
          infuseMenu = 0;
          MonState = 0;
        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }
}


void WifiConf()
{
  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "No") {
        state = 2;
        ui_state = 2;

      }
      else if (dialogbox.getDia() == "Yes") {
        state = 6;
        ui_state = 7;
      }
      break;
    case 3: dialogbox._diaup();
      break;
    case 4: dialogbox._diadwn();
      break;
  }
}

void Sleep()
{
  u8g2.setPowerSave(1);
  switch (get_button())
  {
    case 1: u8g2.setPowerSave(0);
      idle_time = 0;
      sleeper = false;
      state = prev_state;
      break;
    case 3: u8g2.setPowerSave(0);
      sleeper = false;
      idle_time = 0;
      state = prev_state;
      break;
    case 4: u8g2.setPowerSave(0);
      sleeper = false;
      idle_time = 0;
      state = prev_state;
      break;
  }

}
void fin()
{

}

void Developer()
{
  switch (get_button())
  {
    case 1:

      state = 6;
      ui_state = 7;
      break;
  }


}


void ServErr()
{
  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "Ok") {
        state = 2;
        ui_state = 2;

      }
      break;

  }
}
void batlowoff()
{
  if (logo_time > 3500)
  {
    u8g2.setPowerSave(1);
    system_deep_sleep_set_option(2);
    system_deep_sleep(0);
    delay(500);
  }
}
void Infbatchk()
{
  switch (get_button())
  {
    case 1: if (dialogbox1.getDia() == "Ok") {
           ui_state = 3;
            state = 9;

      }
      break;
  }
}
void Batchk()
{
  if (logo_time > 3500)
  {
    ui_state=prev_ui_state;
    state=prev_state;
  }
}

