//#include "U8g2lib.h"
#include "MAINMENU.h"
#include "ICON.h"
#include "icons.h"


#define ENCODER_PINA     5
#define ENCODER_PINB     13
#define ENCODER_BTN      4
int BTN = 0;


  #define update_icon_width 48
#define update_icon_height 48

   
U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/3, /* cs=*/ 10);
String t1="INFUSE";
String t2="SETUP";
String t3="OFFLINE";
String t4="SLEEP";
ICON a[4] = {{t1,ic_opacity_black_24dp_bits,u8g2},{t2,ic_settings_black_24dp_bits,u8g2},{t3,ic_power_settings_new_black_24dp_bits,u8g2},{t4,update_icon_bits,u8g2}};
MAINMENU Menu(0,a,u8g2);
void setup() {

    pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);
  attachInterrupt(ENCODER_PINA, encoder, RISING);
  attachInterrupt(ENCODER_PINB, encoder, RISING);
  // put your setup code here, to run once:
    u8g2.begin();

}

void loop() {
 u8g2.clearBuffer();
//a[3].displaym();
Menu.displayc();
  u8g2.sendBuffer();

 // Menu.up();

  switch (get_button())
{
  case 3: Menu.up();
    break;
  case 4: Menu.dwn();
    break;
}

}
