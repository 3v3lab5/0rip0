#include"DROP.h"

MovingAverageFilter movingAvg(10);

//Calculate Rate(dpm) using Time btwn drops and apply moving Avg//
int DROP::getRate()
{

  if (_Dcount > 0) {
    _rate_ml = (_rate * 60) / _df;
    return _rate;
  }


}


//Returns Rate in Ml/hr// 
int DROP::getRateMl()
{
  if (_Dcount > 0) {
    return _rate_ml;
  }

}

//To get infused volume
int DROP::getvolInf()
{
  _Infvol = (_Dcount / _df);
  return _Infvol;
}
//To get Remaining Volume
int DROP::getvolRem()
{
  _RemVol = (_Tvol - getvolInf());
  return _RemVol;
}

// To get No of drops
long DROP::getDcount()
{
  return _Dcount;
}

//fuction gets the Elapsed time btwn drops from the interrupt nd it incriment the no of drops
void DROP::setTime(unsigned long int drip_time)
{
  _Etime = drip_time;
  _Dcount++;
    _rate = (long)60000 / _Etime;
   newrate = movingAvg.process(_rate);
if(_Etime<1000)
{
_rate=newrate;
}

}

//Set drop factor of the drip set
void DROP::setDf(String dpf)
{
  _df = dpf.toInt();
  _Dcount = 0;
}

//Set Bed ID
void DROP::setBed(String pat)
{
  _Bed = pat;
}

//Set Med ID
void DROP::setMed(String med)
{
  _Med = med;
}

//Set Time Table Id(unique element)
void DROP::setTimetable(String Ttable)
{
_Timetable=Ttable;
}

//Set MEd NAme
void DROP::setMedName(String medname)
{
  _MedName = medname;
}
//Set Patient NAme
void DROP::setNam(String nam)
{
  _Name = nam;
}

//Set Total Volume
void DROP::setTvol(String tvol)
{
  _Tvol = tvol.toInt();
}

//Set Rate to Set
void DROP::setR2set(String rset)
{
  _rate2set = rset.toInt();
}

//Set Alert Percent
void DROP::setAlrt(String alt)
{
  _alert = alt.toInt();
}

//Checks Condition for monitoring and returns 1 if condition is true else 0
int DROP::MonRate()
{
  int err;
  err = getR2setDPM() - _rate;
  if (abs(err) < MON_RANGE)
  {
     if((_Dcount-_setCount)>=3)   /// checks for 3 consecutive drops 
      {
    return 1;
      }
      else
        return 0;
  }
  else {
     _setCount=_Dcount;
    return 0;
  }
}

//Returns The rate to set in ml/hr
int DROP::getrate2set()
{

  return _rate2set;

}

//Returns the rate to set in drops per min (dpm)
int DROP::getR2setDPM()
{

  return ((_rate2set * _df) / 60);

}
//Returns Patient Name
String DROP::getName()
{

  return _Name;

}

//Returns Med ID
String DROP::getMed()
{

  return _Med;

}

//Returns TimeTAble ID
String DROP::getTimetable()
{

	return _Timetable;

}

//Returns Med NAme
String DROP::getMedName()
{

  return _MedName;

}

//Returns Bed Name
String DROP::getBed()
{

  return _Bed;

}

//Returns Total volume for infusion
int DROP::getTvol()
{

  return _Tvol;

}

//To find Infused Percent
int DROP::getinfPercent()
{
	return ((getvolInf()*100) / getTvol());
}

//Returns Drop factor
int DROP::getDf()
{

  return _df;

}
//To find Remaining time for infusion
int DROP::getRtime()
{
  _rTime = ((float)(_Tvol - _Infvol) / _rate) * 60;
  return _rTime;
}

//To find Rate at which to be alerted in ml/hr
int DROP::getAlertPercent()
{
  return (getrate2set() * ALERT_PERCENT);
}

//To find Rate at which to be alerted in  dpm
int DROP::getAlertDrops()
{
  return (getR2setDPM() * ALERT_PERCENT);
}
//To find Total Time for infusion
int DROP::getTtime()
{
  _tTime = ((float)(_Tvol) / _rate2set) * 60;
  return _tTime;
}
//Get Different type of Alerts
int DROP::Alert(unsigned long int _time)
{
  int err;
  err = getrate2set() - _rate_ml;
  _LastEtime = _time;
  if (_LastEtime > (10*_Etime) && getinfPercent()<90)
  {
    return BLOCK;
  }

  else  if (_LastEtime > (10*_Etime) && getinfPercent() >= 90)
  {
    _monCount=_Dcount;  
    return EMPTY;
  }


  else  if (abs(err) > getAlertPercent() && getinfPercent() >2 && getinfPercent() < 90)
  {
   
    if ((_Dcount-_monCount) > getAlertDrops())
    { 
   
      return RATE_ERR;

    }

    else{
	    return NO_ERR;
    }
  }

  else  if (getinfPercent() >= 90 )
  {
   _monCount=_Dcount;
	  return COMPLETED;
  }
  else {
    _monCount = _Dcount;
    return NO_ERR;
  }
}
//default Constructor
DROP::DROP()
{
	newrate=1;
	_rate_ml=1;
	_alert=30;
	_df=60;
	_rate2set=1;
	_Tvol=1;
	_RemVol=1;
	_Infvol=1;
	_Dcount=0;
	_rTime=1;
	_tTime=1;
	_monCount=0;
	_setCount=0;
	_rate=1;
	_Etime=1;
	_LastEtime=1;
}
//default Distructor
DROP::~DROP()
{

}
