#include "Clock.hpp"

// probably use 24 hour to store values but convert on output
Clock::Clock(const int hour, const int minute){
  isPm_ = false;
  minute_ = minute;
  if(hour > 12){
    hour_ = hour - 12;
    isPm_ = true;
  }else if(hour == 0){
    hour_ = 12;
  }else{
    hour_ = hour;
  }
}

int Clock::hour() const{
  return hour_;
}

int Clock::minute() const{
  return minute_;
}

bool Clock::isPm() const{
  return isPm_;
}

bool Clock::hasSameTime(const Clock& clock) const{
  return (isPm_==clock.isPm())
  &&(hour_==clock.hour())
  &&(minute_==clock.minute());
}

void AlarmClock::incrementHour(){
  if(hour_==12){
    hour_ = 1;
    isPm_ = !isPm_;
  }else{
    hour_++;
  }
}

void AlarmClock::incrementMinute(){
  if(minute_==59){
    minute_=0;
  }else{
    minute_++;
  }
}

void AlarmClock::snooze(){
  if(alarmRinging_){
    snoozeCounter_ = 60*2*9;
  }
}

void AlarmClock::decrementSnoozeCounter(){
  if(snoozeCounter_>0){
    snoozeCounter_--;
  }
}

bool AlarmClock::isAlarmRinging() const{
  if((snoozeCounter_>0)||(!alarmRinging_)){
    return false;
  }
  return true;
}

void AlarmClock::startAlarm(){
  if(alarmEnabled_){
    alarmRinging_ = true;
  }
}

void AlarmClock::stopAlarm(){
  alarmRinging_ = false;
}

void AlarmClock::setAlarmEnabled(bool alarmEnabled){
  alarmEnabled_ = alarmEnabled;
}

bool AlarmClock::alarmEnabled() const{
  return alarmEnabled_;
}

int formattedTime(const Clock& clock){
 return (clock.hour()*100)+clock.minute();
}
