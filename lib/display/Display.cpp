#include "Clock.h"
#include "Display.h"

Display::Display(){
  m_matrix = Adafruit_7segment();
  m_matrix.begin(0x70);
}

/*
0000 0010 center colon
0000 0100 left colon upper dot
0000 1000 left colon lower dot
-----
0000 1010 is pm
0000 1110 is pm and alarm enabled
0000 0110 alarm enabled
*/
void Display::setDisplay(Clock* clock, bool alarmEnabled){
  m_matrix.print(formattedTime(clock), DEC);
  bool isPm = clock->isPm();
  if(isPm&&alarmEnabled){
    m_matrix.writeDigitRaw(2, 0x0E);
  }else if(isPm){
    m_matrix.writeDigitRaw(2, 0x0A);
  }else if(alarmEnabled){
    m_matrix.writeDigitRaw(2, 0x06);
  }else{
    m_matrix.drawColon(true);
  }
}

void Display::writeDisplay(){
  m_matrix.writeDisplay();
}
