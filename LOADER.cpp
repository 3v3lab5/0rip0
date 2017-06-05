#include"LOADER.h"


LOADER::LOADER(double _inRad,double _outRad, U8G2 u8)
{
 _u8g2 = u8;
 inRad=_inRad;
 outRad=_outRad;
 i=random(360);
lasti=i; 
}

LOADER::LOADER(double _outRad, U8G2 u8)
{
 _u8g2 = u8;
 outRad=_outRad;
r=random(1,outRad);
speedinc=(float)((rand() % 4 + 1)/3);
}

LOADER::~LOADER()   ///default distructor
{
}

void LOADER::hotspot(){
  if(!speedinc)speedinc=.6;
  r=r+speedinc;
   _u8g2.drawCircle(32,67,r, U8G2_DRAW_UPPER_RIGHT);
     _u8g2.drawCircle(32,67,r, U8G2_DRAW_LOWER_LEFT);
 if(r>outRad)r=0;

}

void LOADER::draw(){
    i+=.3;
   double x = outRad*cos(i);
   double y = outRad*sin(i);
   _u8g2.drawDisc(x+32,y+50,(2+cos(i))*1.5, U8G2_DRAW_ALL);

    double x2 = outRad*cos(i-.8);
   double y2 = outRad*sin(i-.8);
   _u8g2.drawDisc(x2+32,y2+50,(2+cos(i-.8))*1.5, U8G2_DRAW_ALL);

    double x3 = outRad*cos(i-1.6);
   double y3 = outRad*sin(i-1.6);
   _u8g2.drawDisc(x3+32,y3+50,(2+cos(i-1.6))*1.5, U8G2_DRAW_ALL);

    double x4 = outRad*cos(i-2.4);
   double y4 = outRad*sin(i-2.4);
   _u8g2.drawDisc(x4+32,y4+50,(2+cos(i-2.4))*1.5, U8G2_DRAW_ALL);

    double x5 = outRad*cos(i-3.2);
   double y5 = outRad*sin(i-3.2);
   _u8g2.drawDisc(x5+32,y5+50,(2+cos(i-3.2))*1.5, U8G2_DRAW_ALL);
   
 
    lasti=i;
   if(i>360)i=0;
}




