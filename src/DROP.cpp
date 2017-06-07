#include"DROP.h"
#define FILTER 0.50


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

int DROP::getvolRem()
{
  _RemVol = (getvolInf() - _Tvol);
  return _RemVol;
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
  _Dcount = 0;
}

void DROP::setBed(String pat)
{
  _Bed = pat;
}

void DROP::setMed(String med)
{
  _Med = med;
}

void DROP::setMedName(String medname)
{
  _MedName = medname;
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
  if (abs(err) < MON_RANGE)
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

int DROP::getR2setDPM()
{

  return (_rate2set * 60 / _df);

}

String DROP::getName()
{

  return _Name;

}

String DROP::getMed()
{

  return _Med;

}

String DROP::getMedName()
{

  return _MedName;

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
  _rTime = ((float)(_Tvol - _Infvol) / _rate) * 60;
  return _rTime;
}

int DROP::getAlertPercent()
{
  return (getrate2set() * ALERT_PERCENT);
}

int DROP::getAlertDrops()
{
  return (getR2setDPM() * ALERT_PERCENT);
}
int DROP::getTtime()
{
  _tTime = ((float)(_Tvol) / _rate2set) * 60;
  return _tTime;
}

int DROP::Alert(unsigned long int _time)
{
  int err;
  err = _rate2set - _rate_ml;
  _LastEtime = _time;
  if (_LastEtime > 20000 && getRtime() > 4)
  {
    return BLOCK;
  }

  else  if (getvolRem() < 10 && getRtime() < 2)
  {
    return COMPLETED;
  }

  else  if (_LastEtime > 200000 && getRtime() < 4)
  {
    return EMPTY;
  }
  else  if (abs(err) > getAlertPercent() && getRtime() > 3)
  {
   
    if ((_Dcount-_monCount) > getAlertDrops()) {
      return RATE_ERR;

    }

    else{
	    return NO_ERR;
    }
  }
  else {
    _monCount = _Dcount;
    return NO_ERR;
  }
}

