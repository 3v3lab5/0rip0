#include <FS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "MENU.h"
#include "LOADER.h"
#include "DROP.h"
#include "MAX17043.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <elapsedMillis.h>
#include <Ticker.h>
#include "icons.h"

elapsedMillis timeElapsed, logo_time, idle_time; //dataTicker;
MAX17043 batteryMonitor;
Ticker ticker;
float wifirssi;
int stateOfCharge;
float cellVoltage;
boolean startDisplay = false;
boolean sleep = true;
boolean ticker_reached;
boolean sleeper = false;
boolean notified = false;
boolean batchkflag = false;
//#define ENCODER_PINA     0
//#define ENCODER_PINB     2
//#define ENCODER_BTN      4
//#define DROP_PIN        5
#define ENCODER_PINA     5
#define ENCODER_PINB     13
#define ENCODER_BTN      4
#define DROP_PIN        14
#define WAKE_PIN        16
#define IR_PIN        12
#define ADC_PIN        A0
int state = 0;
int prev_state = 0;
int prev_b_state = 0;
int ui_state = 0;
int prev_ui_state = 0;
int ui_x = 0;
int dot_x = 0;
int wifi_status = 0;
int BTN = 0;
int infuseMenu = 1;
int MonState = 0;
int PMonState = 0;
int qos =1;
int radius=5;
const char* VERSION = "0.8";
String DataStatus = "nill";
int lastReconnectAttempt = 0;
#include <U8g2lib.h>
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R1, /* clock=*/ 13, /* data=*/12, /* cs=*/ 1, /* dc=*/ 10, /* reset=*/ 14);
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R1, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10, /* dc=*/ 15, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R1, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10,/* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/3, /* cs=*/ 10);


//char *d_f = "<<back*60*20*\0";n
char *s_up = "wifi conf&wifi conf&update&update&system&system\0";
MENU Setup("Setup", s_up, u8g2);

MENU dpf;
MENU bed;
MENU med;
MENU dialogbox(u8g2);
MENU dialogbox1(u8g2);
LOADER load(4,15,u8g2);
LOADER hotspot(10,u8g2);
LOADER hotspot1(15,u8g2);
LOADER hotspot2(20,u8g2);

DROP _dripo;

char id[30];

//subscribe
char up_channel[50];
char r_channel_df[50];
char r_channel_pat[50];
char r_channel_med[50];
char r_channel_rate[50];
char r_channel_version[50];
char r_channel_update[50];
const char* mqtt_channel_version = "dripo/%s/version";               ///request from server for current version
const char* mqtt_channel_update = "dripo/%s/update";                    /// request from server for update
const char* mqtt_channel_df = "dripo/%s/df";          /// to recieve df details
const char* mqtt_channel_pat = "dripo/%s/bed";                    /// to recieve patient list
const char* mqtt_channel_med = "dripo/%s/med";                    /// to recieve med list
const char* mqtt_channel_r2set = "dripo/%s/rate2set";          /// to recieve patient details

//publish
char pat_channel[50];
char version_channel[50];
char rate_channel[50];
const char* mqtt_channel_myversion = "dripo/%s/myversion";                  ///to send current version
const char* mqtt_channel_rate = "dripo/%s/rate";                  ///to send rate details
const char* mqtt_channel_req = "dripo/%s/req";                  ///to send df details
const char* mqtt_channel_bedreq = "dripo/%s/bed_req";                  ///to send bed details
const char* mqtt_channel_medreq = "dripo/%s/med_req";                  ///to send med details
const char* mqtt_channel_ratereq = "dripo/%s/rate_req";                  ///to send rate details
const char* mqtt_channel_mon = "dripo/%s/mon";                  ///to send start/stop details
const char* mqtt_channel_err = "dripo/%s/err";                  ///to send err details


const int mqtt_port = 1883;
//const char* mqtt_server = "192.168.0.13";
char mqtt_server[40];
//char mqtt_port[6] = "1883";

WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient mqttClient(wclient);


void setup() {

  Wire.begin(2, 0);
     Serial.begin(115200);
       Serial.println("boot drip");
  Wire.beginTransmission(47); // transmit to device #20 (0x20)
  Wire.write(byte(0x10));// sends instruction byte
  Wire.write(byte(0x64));
  //   //byte x = Wire.read(); // sends potentiometer value byte

 stateOfCharge = batteryMonitor.getSoC();
//  stateOfCharge =13;
  if (stateOfCharge < 10)
  {
    ui_state = 12;
    state = 15;
  }
  cellVoltage = batteryMonitor.getVCell();
  Wire.endTransmission();

  pinMode(ADC_PIN, INPUT);
  pinMode(WAKE_PIN, OUTPUT);
  pinMode(IR_PIN, OUTPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(DROP_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DROP_PIN), checkdrop, HIGH);

  attachInterrupt(ENCODER_PINA, encoder, RISING);
  attachInterrupt(ENCODER_PINB, encoder, RISING);
  //u8g2.begin();
  batteryMonitor.reset();
  batteryMonitor.quickStart();
  logo_time = 0;
  ticker.attach(60, ticker_handler);
ESP.wdtDisable();
ESP.wdtEnable(WDTO_8S);
}


void (* myFunc[18])() = {drawLogo, wifi_init, menu_1, menu_2, menu_3, M_infuse, M_setup, M_pwroff, update_dripo, Sho_Rate, WifiConf, Sleep, fin, Developer, ServErr, batlowoff,Infbatchk,Batchk};
void (* UI_Fn[16])() = {UI_Logo, UI_Wifi, UI_Menu, UI_Rate, UI_infuse, UI_Update, UI_Shutdown, UI_Setup, UI_WifiConf, UI_fin, UI_dripo, UI_ServErr, UI_batlow,UI_InfBatChK,UI_batchk,UI_batfull};

void loop() {
  if (startDisplay == false) {
    u8g2.begin();
    startDisplay = true;
  }
  analogWrite(WAKE_PIN, 0);

  u8g2.clearBuffer();
  UI_Fn[ui_state]();
  STBAR();
  u8g2.sendBuffer();
  myFunc[state]();
  yield();
  wifi_status =  wifi_connect(wifi_status);
  DataStatus = send_req(DataStatus);
  yield();

}



