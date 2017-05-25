#ifndef DROP_H
#define DROP_H
#include "Arduino.h"

class DROP
{
private:
//unsigned long int  _Etime;
unsigned long int Filterd_Etime;
//int _rate;
int _rate_ml;
int _alert;
int _df;
int _rate2set;
String _Bed;
String _Med;
String _Name;
String _MedName;

int _Tvol;
int _Infvol;
long _Dcount;
int _rTime;
int _tTime;
int _monCount;
unsigned long int smooth(unsigned long int,float,unsigned long int);

public:

long _rate;
unsigned long int  _Etime;

void setTime(unsigned long int);
int getRate();
int  getRateMl();
int getvolInf();
int getrate2set();
long getDcount();
int getRtime();
int getTtime();
String getName();
String getMed();
String getMedName();

String getBed();

int getTvol();
int getDf();

void setDf(String);
void setBed(String);
void setMed(String);
void setMedName(String);

void setNam(String);
void setTvol(String);
void setR2set(String);
void setAlrt(String);
int MonRate();
//void setAlert();
 
};



#endif
