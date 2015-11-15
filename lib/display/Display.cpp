#include "Clock.h"
#include "Display.h"

Display::Display(){
  m_matrix = Adafruit_7segment();
  m_matrix.begin(0x70);
}

void Display::setDisplay(Clock* clock, bool alarmEnabled){
  m_matrix.print(formattedTime(clock), DEC);
  if(clock->isPm()){
    m_matrix.writeDigitRaw(2, 0x0A);
  }else{
    m_matrix.drawColon(true);
  }
}

void Display::writeDisplay(){
  m_matrix.writeDisplay();
}
