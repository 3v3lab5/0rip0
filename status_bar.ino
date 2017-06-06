void STBAR()
{
  ESP.wdtFeed();
  if (state == 2 || state == 3 || state == 4 || state == 9 || state == 7 || state == 10 || infuseMenu == 3 || state == 17) {
    //  stateOfCharge = batteryMonitor.getSoC();
    stateOfCharge = 25;
    float  widthCharge = map(stateOfCharge, 0, 100, 1, 7.5);
    u8g2.drawXBM(42, 0, battery_width, battery_height, battery_bits);
    for(float i=0;i<=widthCharge;i++)
    {
       u8g2.drawLine(44+i*2, 5,44+i*2, 9);
    }
//    u8g2.drawBox(44, 5, widthCharge, 5);
    
    wifirssi = WiFi.RSSI();
    int  widthwifi = map(wifirssi, -95, 0, 1,4);
    if (WiFi.status() == WL_CONNECTED)
    {
    for(int i=0;i<=widthwifi;i++)
    {
   u8g2.drawCircle(0,11,i*3, U8G2_DRAW_UPPER_RIGHT);
   }

    }
    else{
     //add wifi no connection icon here 
   u8g2.drawXBM(0,0 , nowifi_width, nowifi_height, nowifi_bits);

    
    }
    if (stateOfCharge > 85) {
      if (stateOfCharge == 100 && batchkflag == false)
      {
        logo_time = 0;
        prev_ui_state = ui_state;
        prev_b_state = state;
        ui_state = 15;
        state = 17;
        batchkflag = true;
      }
    }
    else if (stateOfCharge > 20)
    {
      batchkflag = false;
    }
    else if (stateOfCharge < 20)
    {
      if (stateOfCharge > 15)
      {
        batchkflag = false;
      }
      if (stateOfCharge < 15 && batchkflag == false)
      {
        logo_time = 0;
        prev_b_state = state;
        prev_ui_state = ui_state;
        ui_state = 14;
        state = 17;
        batchkflag = true;
      }
      else if (stateOfCharge < 12)
      {
        ui_state = 12;
        state = 15;
      }

    }

    if (MonState == 3 || (PMonState == 3 && MonState == 1)) {
      u8g2.drawXBM(1, -1, monitor_width, monitor_height, monitor_bits);
    }

    if (idle_time > 120000 && sleeper == false)
    {
      sleeper = true;
      prev_state = state;
      state = 11;
    }
    sleep = false;
//    if (WiFi.status() == WL_CONNECTED)
//    {
//
//
//
//      u8g2.drawXBM(0, 3, stwifi_width, stwifi_height, stwifi_bits);
//
//      if (wifirssi < 0 && wifirssi > -65)
//      {
//
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(16, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(22, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(28, 9, 2, U8G2_DRAW_ALL);
//      }
//
//      else if (wifirssi < -65 && wifirssi > -75)
//      {
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(16, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(22, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(28, 9, 2, U8G2_DRAW_ALL);
//      }
//      else if (wifirssi < -75 && wifirssi > -85)
//      {
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawDisc(16, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(22, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(28, 9, 2, U8G2_DRAW_ALL);
//      }
//
//      else if (wifirssi < -85 && wifirssi > -91)
//      {
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_ALL);
//
//        u8g2.drawCircle(16, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(22, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(28, 9, 2, U8G2_DRAW_ALL);
//      }
//
//      else if (wifirssi < -91 && wifirssi > -95)
//      {
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_LOWER_LEFT);
//        u8g2.drawDisc(10, 9, 2, U8G2_DRAW_UPPER_LEFT);
//        u8g2.drawCircle(16, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(22, 9, 2, U8G2_DRAW_ALL);
//        u8g2.drawCircle(28, 9, 2, U8G2_DRAW_ALL);
//      }
//      u8g2.drawCircle(10, 9, 2, U8G2_DRAW_ALL);
//      u8g2.drawCircle(16, 9, 2, U8G2_DRAW_ALL);
//      u8g2.drawCircle(22, 9, 2, U8G2_DRAW_ALL);
//      u8g2.drawCircle(28, 9, 2, U8G2_DRAW_ALL);
//    }
//
//    else
//    {
//      u8g2.drawXBM(30, -1, ic_signal_wifi_off_width, ic_signal_wifi_off_height, ic_signal_wifi_off_bits);
//    }
    u8g2.setDrawColor(1);

  }


}

