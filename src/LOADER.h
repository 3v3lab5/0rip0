#ifndef LOADER_H
#define LOADER_H
#include "Arduino.h"
#include "U8g2lib.h"
class LOADER
{
  private:
  
    U8G2 _u8g2;
    double inRad;
    double outRad,speedInc;
    float speedinc;
    float i,lasti,r;
   
  public:
 
    LOADER(double,double,U8G2 u8);
    LOADER(double,U8G2 u8);
    void hotspot();
    ~LOADER();
    void draw();

};



#endif
