#include"DROP.h"
#define FILTER 0.92


int DROP::getRate()
{

  if (_Dcount > 0) {
    Filterd_Etime = smooth(_Etime, FILTER, Filterd_Etime);
    _rate = (long)60000 / Filterd_Etime;
    return _rate;
  }


}

int DROP::getRateMl()
{
  if (_Dcount > 0) {
    Filterd_Etime = smooth(_Etime, FILTER, Filterd_Etime);

    _rate = (long)60000 / Filterd_Etime;
    _rate_ml = _rate * 60 / _df;
    return _rate_ml;
  }

}


int DROP::getvolInf()
{
  _Infvol = (_Dcount / _df);
  return _Infvol;
}

long DROP::getDcount()
{
  return _Dcount;
}

void DROP::setTime(unsigned long int drip_time)
{
  _Etime = drip_time;
  _Dcount++;

}


unsigned long int DROP::smooth(unsigned long int data, float filterVal, unsigned long int smoothedVal) {


  if (filterVal > 1) {
    filterVal = .99;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (unsigned long int)smoothedVal;
}


void DROP::setDf(String dpf)
{
  _df = dpf.toInt();
  _Dcount=0;
}

void DROP::setBed(String pat)
{
  _Bed = pat;
}

void DROP::setMed(String med)
{
  _Med = med;
}
void DROP::setNam(String nam)
{
  _Name = nam;
}
void DROP::setTvol(String tvol)
{
  _Tvol = tvol.toInt();
}
void DROP::setR2set(String rset)
{
  _rate2set = rset.toInt();
}
void DROP::setAlrt(String alt)
{
  _alert = alt.toInt();
}
int DROP::MonRate()
{
  int err;
  err = _rate2set - _rate_ml;
  if (abs(err) < 10)
  {
   // if((_Dcount-_monCount)>=3)
  //  {
    return 1;
  //  }
  //  else
    //    return 0;
  }
  else {
   // _monCount=_Dcount;
    return 0;
  }
}

int DROP::getrate2set()
{

  return _rate2set;

}

String DROP::getName()
{

  return _Name;

}

String DROP::getMed()
{

  return _Med;

}
String DROP::getBed()
{

  return _Bed;

}
int DROP::getTvol()
{

  return _Tvol;

}

int DROP::getDf()
{

  return _df;

}

int DROP::getRtime()
{
  _rTime = ((float)(_Tvol - _Infvol) / _rate)*60;
  return _rTime;
}

