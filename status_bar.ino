void STBAR()
{

  if (state == 2 || state == 3 || state == 4 || state == 9 || state == 7 || state == 10 || infuseMenu == 3) {
 //   int stateOfCharge = batteryMonitor.getSoC();
    //u8g2.setDrawColor(2);
    //      u8g2.drawFrame(0, 0,64, 128);

 //   u8g2.drawBox(0, 0, 64, 14);
    //u8g2.drawHLine(0, 15, 64);

 //   u8g2.setDrawColor(0);

if(stateOfCharge>85){

     u8g2.drawXBM(54, 2, bat_ful_width,bat_ful_height, bat_ful_bits);

}
else if(stateOfCharge>70)
{
    u8g2.drawXBM(54, 2, bat_80_width,bat_80_height, bat_80_bits);
 
}
else if(stateOfCharge>50)
{
     u8g2.drawXBM(54, 2, bat_60_width,bat_60_height, bat_60_bits);

}

else if(stateOfCharge>30)
{
   u8g2.drawXBM(54, 2, bat_40_width,bat_40_height, bat_40_bits);

}

else if(stateOfCharge>20)
{
   u8g2.drawXBM(54, 2, bat_20_width,bat_20_height, bat_20_bits);
}
else if(stateOfCharge<20)
{
   u8g2.drawXBM(54, 2, bat_empty_width,bat_empty_height, bat_empty_bits);

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
    sleep=false;
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

