#ifndef ERR_HANDLER_H
#define ERR_HANDLER_H
#include<U8g2lib.h>
#include <ESP8266HTTPClient.h>
#include<Arduino.h>
#define ACKD 102
#define NOACKD 105
class ERR_HANDLER
{

	private:
		bool STA_ACK;
		bool DEV_ACK;
		int ERR;
		char ID[30];
		String MED;
		U8G2 _u8g2;
		PubSubClient *mqttclnt;
	public:
		ERR_HANDLER(U8G2 u8,PubSubClient *mqclnt);
		void display_err(int,bool,bool,char[],String);
		void err_alerttype1();
		void err_alerttype2();


};




#endif


