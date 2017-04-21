#include "MENU.h"
#include"DROP.h"
#include "MAX17043.h"
#include "Wire.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <elapsedMillis.h>
#include <Ticker.h>

elapsedMillis timeElapsed,logo_time, idle_time;//dataTicker;
MAX17043 batteryMonitor;
Ticker ticker;

boolean ticker_reached;
boolean sleeper=false;

#define ENCODER_PINA     0
#define ENCODER_PINB     2
#define ENCODER_BTN      4
#define DROP_PIN        5

//#define ENCODER_PINA     5
//#define ENCODER_PINB     13
//#define ENCODER_BTN      4
//#define DROP_PIN        14

int state = 0;
int prev_state=0;
int ui_state = 0;
int ui_x = 0;
int wifi_status = 0;
int BTN = 0;
int infuseMenu = 0;
int MonState = 0;
int PMonState = 0;

String DataStatus = "nill";

#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R1, /* clock=*/ 13, /* data=*/12, /* cs=*/ 1, /* dc=*/ 10, /* reset=*/ 14);
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R1, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10, /* dc=*/ 15, /* reset=*/ U8X8_PIN_NONE);


//char *d_f = "<<back*60*20*\0";
char *s_up = "wifi conf&wifi conf&update&update&\0";
MENU Setup("Setup", s_up, u8g2);

MENU dpf;
MENU bed;
MENU med;
MENU dialogbox(u8g2);
DROP _dripo;

  char id[30];

//subscribe
char up_channel[50];
char r_channel_df[50];
char r_channel_pat[50];
char r_channel_med[50];
char r_channel_rate[50];

const char* mqtt_server = "192.168.0.14";
const char* mqtt_channel_update = "dripo/%s/update";                    /// update
const char* mqtt_channel_df = "dripo/%s/df";          /// to recieve df details
const char* mqtt_channel_pat = "dripo/%s/bed";                    /// to recieve patient list
const char* mqtt_channel_med = "dripo/%s/med";                    /// to recieve med list
const char* mqtt_channel_r2set = "dripo/%s/rate2set";          /// to recieve patient details

//publish
char pat_channel[50];
char rate_channel[50];
const char* mqtt_channel_rate = "dripo/%s/rate";                  ///to send rate details
const char* mqtt_channel_req = "dripo/%s/req";                  ///to send df details
const char* mqtt_channel_bedreq = "dripo/%s/bed_req";                  ///to send bed details
const char* mqtt_channel_medreq = "dripo/%s/med_req";                  ///to send med details
const char* mqtt_channel_ratereq = "dripo/%s/rate_req";                  ///to send rate details
const char* mqtt_channel_mon = "dripo/%s/mon";                  ///to send rate details


const int mqtt_port = 1883;
WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient mqttClient(wclient);


void setup() {

  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(DROP_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DROP_PIN), checkdrop, HIGH);

  attachInterrupt(ENCODER_PINA, encoder, RISING);
  attachInterrupt(ENCODER_PINB, encoder, RISING);
  u8g2.begin();
  batteryMonitor.reset();
  batteryMonitor.quickStart();
  logo_time=0;
  ticker.attach(15, ticker_handler);



}


void (* myFunc[13])() = {drawLogo, wifi_init, menu_1, menu_2, menu_3, M_infuse, M_setup, M_pwroff, update_dripo, Sho_Rate, WifiConf,Sleep,fin};
void (* UI_Fn[10])() = {UI_Logo, UI_Wifi, UI_Menu, UI_Rate, UI_infuse, UI_Update, UI_Shutdown, UI_Setup, UI_WifiConf, UI_fin};

void loop() {

 u8g2.clearBuffer();
  UI_Fn[ui_state]();
  STBAR();


 u8g2.sendBuffer();

 myFunc[state]();

  yield();
  wifi_status =  wifi_connect(wifi_status);
  DataStatus= send_req(DataStatus); 
  yield();
}



