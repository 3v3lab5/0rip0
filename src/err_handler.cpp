#include "err_handler.h"




bool ERR_HANDLER::display_err(String Ttab, int alt, bool ack_dev, bool ack_sta,char id[30],String med,int rate,int infvol,int rtime,int tvol)
{
	STA_ACK=ack_sta;
	DEV_ACK=ack_dev;
	ERR= alt;
	strcpy(ID,id);
	MED=med;
	RATE=rate;
	INFVOL=infvol;
	RTIME=rtime;
	TVOL=tvol;
	_Timetable=Ttab;	

	if(DEV_ACK==true)
	{

		err_alerttype3();
		return false;

	}
	 if(STA_ACK==false&&DEV_ACK==false)
		{

			err_alerttype1();
			return false;
		}
	 if(STA_ACK==true&&DEV_ACK==false)
	 {
	 		err_alerttype2();
	 		return false;

	 }

}


ERR_HANDLER::ERR_HANDLER(U8G2 u8,PubSubClient mqclnt)
{
_u8g2=u8;
mqttclnt=mqclnt;
wasExecuted1=false;
wasExecuted2=false;
wasExecuted3=false;
wasExecuted1=false;

}
void ERR_HANDLER::err_alerttype1()
{//add buzzer code here
	_u8g2.setFont(u8g2_font_crox2h_tr);
			if(ERR==405)
			{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Block")/2),115);	
					_u8g2.print("Block");
					_u8g2.setDrawColor(1);
					if(wasExecuted1==false){
					mqttsenderror("Block");
					wasExecuted1=true;
					}
				}
			else if(ERR==404)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Empty")/2),115);
					_u8g2.print("Empty");
					_u8g2.setDrawColor(1);
					if(wasExecuted2==false){
					mqttsenderror("Empty");
					wasExecuted2=true;}	
				}
			else if(ERR=406)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Rate Err")/2),115);
					_u8g2.print("Rate Err");
					_u8g2.setDrawColor(1);
					
					if(wasExecuted3==false){
					mqttsenderror("Rate Err");
					wasExecuted3=true;}
				}
			else if(ERR=101)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Complete")/2),115);
					_u8g2.print("Complete");
					_u8g2.setDrawColor(1);
				
					if(wasExecuted4==false){
					mqttsenderror("Complete");
                                        wasExecuted4=true;}
				}
}

void ERR_HANDLER::err_alerttype2()
{
	_u8g2.setFont(u8g2_font_crox2h_tr);
			if(ERR==405)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Block")/2),115);	
					_u8g2.print("Block");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);


				}
			else if(ERR==404)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Empty")/2),115);
					_u8g2.print("Empty");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);
				}
			else if(ERR=406)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Rate Err")/2),115);
					_u8g2.print("Rate Err");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);
		
				}
			else if(ERR=101)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Complete")/2),115);
					_u8g2.print("Complete");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);

				}
}
//function to publish error
void ERR_HANDLER::mqttsenderror(char errortype[20])
{

	const char* mqtt_channel_error="dripo/%s/mon";
	char error_channel[50];
	char e_data[80];
	String medi=MED+"-"+_Timetable+"-"+errortype;
	  const char* chr = medi.c_str();
	  sprintf(e_data,"%s-%d-%d-%d-%d",chr,RATE,INFVOL,RTIME,TVOL);
	    if (mqttclnt.connected()) 
	    {
	    	sprintf(error_channel,mqtt_channel_error,ID);
	    	mqttclnt.publish(error_channel, e_data,true);
		}
	      
}


void ERR_HANDLER::err_alerttype3()
{

			if(ERR==405)
				{
				
					mqttsenderror("Block_ACK");
			
				}
			else if(ERR==404)
				{
				
					mqttsenderror("Empty_ACK");
				}
			else if(ERR=406)
				{
			
					mqttsenderror("Rate Err_ACK");
				}
			else if(ERR=101)
				{
				
					mqttsenderror("Complete_ACK");
				}


}

void ERR_HANDLER::wasExecuted()

{
wasExecuted1=false;
wasExecuted2=false;
wasExecuted3=false;
wasExecuted4=false;
}
