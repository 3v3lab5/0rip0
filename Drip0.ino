#include <FS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "src/err_handler.h"
#include "src/MENU.h"
#include "src/LOADER.h"
#include "src/DROP.h"
#include "MAX17043.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <elapsedMillis.h>
#include <Ticker.h>
#include "src/icons.h"
#include "src/MAINMENU.h"
#include "src/ICON.h"
#include "src/icons.h"
elapsedMillis timeElapsed, logo_time, idle_time; //dataTicker;
MAX17043 batteryMonitor;
Ticker ticker;
float wifirssi;
int stateOfCharge;
float cellVoltage;
boolean startDisplay = false;
boolean sleep = false;
boolean ticker_reached;
boolean sleeper = false;
boolean notified = false;
boolean batchkflag = false;
boolean staAck = false;
boolean devAck = false;

#define BUZZ_PIN        15
#define ENCODER_PINA     5
#define ENCODER_PINB     13
#define ENCODER_BTN      4
#define DROP_PIN        14
#define WAKE_PIN        16
#define IR_PIN        12
#define ADC_PIN        A0
int altmsg = NO_ERR;
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
int qos = 1;
int radius = 5;
int connection = 0;
int  switchon =1000;
const char* VERSION = "0.8";
String DataStatus = "nill";
long lastReconnectAttempt = 0;
unsigned long acktime;

unsigned long int logtime=0;
int logstatus=0;


long lastDAttempt = 0;
int detect1=2;
int detect2=0;

int irAmp=350;   //set ir value to zero

U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/3, /* cs=*/ 10);

String t1 = "INFUSE";
String t2 = "SETUP";
String t3 = "OFFLINE";
String t4 = "SLEEP";
ICON a[4] = {{t1, ic_opacity_black_24dp_bits, u8g2}, {t2, ic_settings_black_24dp_bits, u8g2}, {t3, offline_bits, u8g2}, {t4, ic_power_settings_new_black_24dp_bits, u8g2}};
MAINMENU Menu(0, a, u8g2);
//char *d_f = "<<back&<<back&15&15&20&20&60&60\0";
//int Off_vol =50;
//int Off_Rate=5;
char *s_up = "wifi conf&wifi conf&update&update&system&system\0";
MENU Setup("Setup", s_up, u8g2);
//MENU Off_dpf("Dpf",d_f,u8g2);
MENU dpf;
MENU bed;
MENU med;
MENU dialogbox(u8g2);
MENU dialogbox1(u8g2);
LOADER load(4, 15, u8g2);
LOADER hotspot(10, u8g2);
LOADER hotspot1(15, u8g2);
LOADER hotspot2(20, u8g2);

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
char r_channel_staAck[50];
const char* mqtt_channel_version = "dripo/%s/version";               ///request from server for current version
const char* mqtt_channel_update = "dripo/%s/update";                    /// request from server for update
const char* mqtt_channel_df = "dripo/%s/df";          /// to recieve df details
const char* mqtt_channel_pat = "dripo/%s/bed";                    /// to recieve patient list
const char* mqtt_channel_med = "dripo/%s/med";                    /// to recieve med list
const char* mqtt_channel_r2set = "dripo/%s/rate2set"; /// to recieve patient details
const char* mqtt_channel_staAck = "dripo/%s/staAck"; /// station ack

//publish
char pat_channel[50];
char version_channel[50];
char rate_channel[50];
char log_channel[50];

char staAck_channel[50];
const char* mqtt_channel_myversion = "dripo/%s/myversion";                  ///to send current version
//const char* mqtt_channel_rate = "dripo/%s/rate";                  ///to send rate details
const char* mqtt_channel_req = "dripo/%s/req_df";                  ///to send df details
const char* mqtt_channel_bedreq = "dripo/%s/bed_req";                  ///to send bed details
const char* mqtt_channel_medreq = "dripo/%s/med_req";                  ///to send med details
const char* mqtt_channel_ratereq = "dripo/%s/rate_req";                  ///to send rate details
const char* mqtt_channel_mon = "dripo/%s/mon";                  ///to send start/stop details
const char* mqtt_channel_log = "dripo/%s/log";                  ///to send err details
//const char* mqtt_channel_devack = "dripo/%s/ack_dev";       /// to publish dev ack

const int mqtt_port = 1883;
char* mqtt_server = "192.168.0.13";
//char mqtt_server[40];
//char mqtt_port[6] = "1883";

WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient mqttClient(wclient);

ERR_HANDLER _errAlert(u8g2, mqttClient);

void setup() {

  Wire.begin(2, 0);
  Serial.begin(115200);

  Serial.println("boot drip");

  stateOfCharge = batteryMonitor.getSoC();

  if (stateOfCharge < 5)
  {
    ui_state = 12;
    state = 15;
  }
  cellVoltage = batteryMonitor.getVCell();

  pinMode(ADC_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(WAKE_PIN, OUTPUT);
  pinMode(IR_PIN, OUTPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(DROP_PIN, INPUT_PULLUP);
 // analogWrite(WAKE_PIN,switchon);

  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DROP_PIN), checkdrop, HIGH);

  attachInterrupt(ENCODER_PINA, encoder, RISING);
  attachInterrupt(ENCODER_PINB, encoder, RISING);
  //u8g2.begin();
  batteryMonitor.reset();
  batteryMonitor.quickStart();
  logo_time = 0;
  ticker.attach(30, ticker_handler);
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
  u8g2.begin();

}


void (* myFunc[19])() = {drawLogo, wifi_init, menu_1, menu_2, menu_3, M_infuse, M_setup, M_pwroff, update_dripo, Sho_Rate, WifiConf, Sleep, fin, Developer, ServErr, batlowoff, Infbatchk, Batchk,SensorCalib};
void (* UI_Fn[17])() = {UI_Logo, UI_Wifi, UI_Menu, UI_Rate, UI_infuse, UI_Update, UI_Shutdown, UI_Setup, UI_WifiConf, UI_fin, UI_dripo, UI_ServErr, UI_batlow, UI_InfBatChK, UI_batchk, UI_batfull, UI_Calib};

void loop() {

  digitalWrite(WAKE_PIN, LOW);
//analogWrite(WAKE_PIN,switchon);
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




