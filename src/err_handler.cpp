#include "err_handler.h"




void ERR_HANDLER::display_err(int alt, bool ack_dev, bool ack_sta)
{
STA_ACK=ack_sta;
DEV_ACK=ack_dev;
ERR= alt;
 if(STA_ACK==false&&DEV_ACK==false)
 {
	_u8g2.setFont(u8g2_font_crox2h_tr);
_u8g2.setCursor(0,92);
_u8g2.print("Err");
_u8g2.setCursor(30,92);
_u8g2.print(ERR);

 }

}


ERR_HANDLER::ERR_HANDLER(U8G2 u8)
{
_u8g2=u8;

}


