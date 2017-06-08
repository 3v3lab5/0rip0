#include "err_handler.h"




void ERR_HANDLER::display_err(int alt, bool ack_dev, bool ack_sta,char id[30],String med)
{
	STA_ACK=ack_sta;
	DEV_ACK=ack_dev;
	ERR= alt;
	ID=id;
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


ERR_HANDLER::ERR_HANDLER(U8G2 u8,PubSubClient &mqclnt)
{
_u8g2=u8;
//mqttclnt=mqclnt;

}
void ERR_HANDLER::err_alerttype1()
{//add buzzer code here
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