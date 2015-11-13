#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

struct Clock {
  int hour;
  int minute;
  bool isPm;
};
Clock alarm = {6, 50, false};
RTC_DS1307 rtc;
Adafruit_7segment matrix = Adafruit_7segment();
int alarmViewButton = 9;
int alarmMinuteSetButton = 8;
int alarmHourSetButton = 7;

void setup () {
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  matrix.begin(0x70);
  pinMode(alarmViewButton, INPUT_PULLUP);
  pinMode(alarmMinuteSetButton, INPUT_PULLUP);
  pinMode(alarmHourSetButton, INPUT_PULLUP);
}

void loop () {
    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    bool isPm = false;
    if (hour > 12){
      hour = hour - 12;
      isPm = true;
    }else if (hour == 0){
      hour = 12;
    }
    int timeToDisplay = (hour*100)+minute;
    if(digitalRead(alarmViewButton)==LOW){
      if(digitalRead(alarmMinuteSetButton)==LOW){
        if(alarm.minute==59){
          alarm.minute=0;
        }else{
          alarm.minute++;
        }
      }
      if(digitalRead(alarmHourSetButton)==LOW){
        if(alarm.hour==12){
          alarm.hour=1;
          alarm.isPm=!alarm.isPm;
        }else{
          alarm.hour++;
        }
      }
      timeToDisplay = (alarm.hour*100)+alarm.minute;
      isPm = alarm.isPm;
    }
    matrix.print(timeToDisplay, DEC);
    if(isPm){
      matrix.writeDigitRaw(2, 0x0A);
    }else{
      matrix.drawColon(true);
    }
    matrix.writeDisplay();
    delay(500);
}
