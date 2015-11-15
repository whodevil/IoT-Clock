#include "Clock.h"

Clock::Clock(int hour, int minute){
  m_isPm = false;
  m_minute = minute;
  if(hour > 12){
    m_hour = hour - 12;
    m_isPm = true;
  }else if(hour == 0){
    m_hour = 12;
  }else{
    m_hour = hour;
  }
}

int Clock::hour(){
  return m_hour;
}

int Clock::minute(){
  return m_minute;
}

bool Clock::isPm(){
  return m_isPm;
}

bool Clock::equals(Clock* clock){
  return (m_isPm==clock->isPm())
  &&(m_hour==clock->hour())
  &&(m_minute==clock->minute());
}

AlarmClock::AlarmClock():Clock(6,50){
  m_snoozeCounter = 0;
  m_alarmRinging = false;
  m_alarmEnabled = false;
}

void AlarmClock::incrementHour(){
  if(m_hour==12){
    m_hour = 1;
    m_isPm = !m_isPm;
  }else{
    m_hour++;
  }
}

void AlarmClock::incrementMinute(){
  if(m_minute==59){
    m_minute=0;
  }else{
    m_minute++;
  }
}

void AlarmClock::snooze(){
  if(m_alarmRinging){
    m_snoozeCounter = 60*2*9;
  }
}

void AlarmClock::decrementSnoozeCounter(){
  if(m_snoozeCounter>0){
    m_snoozeCounter--;
  }
}

bool AlarmClock::isAlarmRinging(){
  if((m_snoozeCounter>0)||(!m_alarmRinging)){
    return false;
  }
  return true;
}

void AlarmClock::startAlarm(){
  if(m_alarmEnabled){
    m_alarmRinging = true;
  }
}

void AlarmClock::stopAlarm(){
  m_alarmRinging = false;
}

void AlarmClock::setAlarmEnabled(bool alarmEnabled){
  m_alarmEnabled = alarmEnabled;
}

bool AlarmClock::alarmEnabled(){
  return m_alarmEnabled;
}

int formattedTime(Clock* clock){
 return (clock->hour()*100)+clock->minute();
}
