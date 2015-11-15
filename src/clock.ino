#include <Wire.h>
#include "RTClib.h"
#include "Clock.h"
#include "Display.h"

#define VIEW_BUTTON 9
#define SET_MINUTE_BUTTON 8
#define SET_HOUR_BUTTON 7
#define SNOOZE_BUTTON 6
#define ENABLE_ALARM_BUTTON 5

RTC_DS1307 rtc;
Display* display;
AlarmClock* alarm;

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

  alarm = new AlarmClock();
  display = new Display();
  pinMode(VIEW_BUTTON, INPUT_PULLUP);
  pinMode(SET_MINUTE_BUTTON, INPUT_PULLUP);
  pinMode(SET_HOUR_BUTTON, INPUT_PULLUP);
  pinMode(ENABLE_ALARM_BUTTON, INPUT_PULLUP);
  pinMode(SNOOZE_BUTTON, INPUT_PULLUP);
}

void loop () {
  DateTime now = rtc.now();
  Clock* clock = new Clock(now.hour(), now.minute());
  if(digitalRead(VIEW_BUTTON)==LOW){
    if(digitalRead(SET_MINUTE_BUTTON)==LOW){
      alarm->incrementMinute();
    }
    if(digitalRead(SET_HOUR_BUTTON)==LOW){
      alarm->incrementHour();
    }
    delete clock;
    clock = alarm;
  }else if(digitalRead(ENABLE_ALARM_BUTTON)==LOW){
    alarm->setAlarmEnabled(!alarm->alarmEnabled());
  }

  display->setDisplay(clock, alarm->alarmEnabled());
  display->writeDisplay();
  delay(500);
}
