void STBAR()
{

  if (state == 2 || state == 3 || state == 4 || state == 9 || state == 7 || state == 10 || infuseMenu == 3) {
    int stateOfCharge = batteryMonitor.getSoC();
    //u8g2.setDrawColor(2);
    //      u8g2.drawFrame(0, 0,64, 128);

    u8g2.drawBox(0, 0, 64, 14);
    //u8g2.drawHLine(0, 15, 64);

    u8g2.setDrawColor(0);
   u8g2.drawXBM(47, -1, ic_battery_60_black_15dp_width,ic_battery_60_black_15dp_height, ic_battery_60_black_15dp_bits);
    u8g2.setFont(u8g2_font_crox2h_tr);
    u8g2.setCursor(0,11);
    u8g2.print(stateOfCharge);
 
    if (MonState == 3 || (PMonState == 3 && MonState == 1)) {
      u8g2.drawXBM(1, -1, monitor_width, monitor_height, monitor_bits);
    }

    if (idle_time > 120000 && sleeper == false)
    {
      sleeper = true;
      prev_state = state;
      state = 11;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      u8g2.drawXBM(30, -1, stwifi_width, stwifi_height, stwifi_bits);
    }

    else
    {
      u8g2.drawXBM(30, -1, ic_signal_wifi_off_width, ic_signal_wifi_off_height, ic_signal_wifi_off_bits);
    }
    u8g2.setDrawColor(1);
  }


}

