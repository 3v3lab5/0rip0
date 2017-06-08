#ifndef ERR_HANDLER_H
#define ERR_HANDLER_H
#include<U8g2lib.h>
#include<Arduino.h>
#define ACKD 102
#define NOACKD 105
class ERR_HANDLER
{

	private:
		bool STA_ACK;
		bool DEV_ACK;
		int ERR;
		U8G2 _u8g2;
	public:
		ERR_HANDLER(U8G2 u8);
		void display_err(int,bool,bool);


};




#endif

