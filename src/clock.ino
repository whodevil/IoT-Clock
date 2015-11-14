#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Clock.h"

#define VIEW_BUTTON 9
#define SET_MINUTE_BUTTON 8
#define SET_HOUR_BUTTON 7

RTC_DS1307 rtc;
Adafruit_7segment matrix = Adafruit_7segment();
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
  matrix.begin(0x70);
  alarm = new AlarmClock();
  pinMode(VIEW_BUTTON, INPUT_PULLUP);
  pinMode(SET_MINUTE_BUTTON, INPUT_PULLUP);
  pinMode(SET_HOUR_BUTTON, INPUT_PULLUP);
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
  }
  matrix.print(formattedTime(clock), DEC);
  if(clock->isPm()){
    matrix.writeDigitRaw(2, 0x0A);
  }else{
    matrix.drawColon(true);
  }
  matrix.writeDisplay();
  delay(500);
}
