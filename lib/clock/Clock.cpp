#include "clock.h"

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

AlarmClock::AlarmClock():Clock(6,50){}

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

int formattedTime(Clock* clock){
 return (clock->hour()*100)+clock->minute();
}
