#include "err_handler.h"




void ERR_HANDLER::display_err(int alt, bool ack_dev, bool ack_sta,char id[30],String med)
{
	STA_ACK=ack_sta;
	DEV_ACK=ack_dev;
	ERR= alt;
	strcpy(ID,id);
	MED=med;
	 if(STA_ACK==false&&DEV_ACK==false)
		{

			err_alerttype1();
		}
	 if(STA_ACK==true&&DEV_ACK==false)
	 {
	 		err_alerttype2();
	 }

}


ERR_HANDLER::ERR_HANDLER(U8G2 u8,PubSubClient mqclnt)
{
_u8g2=u8;
mqttclnt=mqclnt;

}
void ERR_HANDLER::err_alerttype1()
{//add buzzer code here
	_u8g2.setFont(u8g2_font_crox2h_tr);
	_u8g2.setCursor(0,92);
			if(ERR==405)
				{
					_u8g2.print("Block");
					mqttsenderror("Block");
				}
			else if(ERR==404)
				{
					_u8g2.print("Empty");
					mqttsenderror("Empty");

				}
			else if(ERR=406)
				{
					_u8g2.print("Rate Err");
					mqttsenderror("Rate Err");

				}
			else if(ERR=101)
				{
					_u8g2.print("Complete");
					mqttsenderror("Complete");

				}
}

void ERR_HANDLER::err_alerttype2()
{
	_u8g2.setFont(u8g2_font_crox2h_tr);
	_u8g2.setCursor(0,92);
			if(ERR==405)
				{
					_u8g2.print("Block");


				}
			else if(ERR==404)
				{
					_u8g2.print("Empty");

				}
			else if(ERR=406)
				{
					_u8g2.print("Rate Err");
		
				}
			else if(ERR=101)
				{
					_u8g2.print("Complete");

				}
}
void ERR_HANDLER::mqttsenderror(char errortype[30])
{

	//write mqtt publish code here
	const char* mqtt_channel_error="dripo/%s/error";
	char error_channel[50];
	char e_data[50];
	  const char* chr = MED.c_str();
	  sprintf(e_data, "%s-%s", chr,errortype);
	    if (mqttclnt.connected()) {
	    sprintf(error_channel,mqtt_channel_error,ID);
	    mqttclnt.publish(error_channel, e_data);
	}
	      
}