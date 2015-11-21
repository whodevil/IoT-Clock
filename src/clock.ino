#include <Wire.h>
#include <SoftwareSerial.h>
#include "RTClib.h"
#include "Clock.h"
#include "Display.h"

#define VIEW_BUTTON 9
#define SET_MINUTE_BUTTON 8
#define SET_HOUR_BUTTON 7
#define SNOOZE_BUTTON 6
#define ENABLE_ALARM_SWITCH 5
#define VOICE_RX 10
#define VOICE_TX 11

RTC_DS1307 rtc;
Display* display;
AlarmClock* alarm;
SoftwareSerial voiceSerial = SoftwareSerial(VOICE_RX, VOICE_TX);

void setup () {
  setupPins();
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  initVoice();
  initRtc();
  alarm = new AlarmClock();
  display = new Display();
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


  // voiceSerial.print('S');
  // voiceSerial.print("Good morning Dev\/\/on and Lorraine, time to wake up! The weather is rainy and your first meeting is at 9:30.");
  // voiceSerial.print("\n");
  // while (voiceSerial.read() != ':');
  handleAlarmEnabledSwitch();

  display->setDisplay(clock, alarm->alarmEnabled());
  display->writeDisplay();
  delay(500);
}

void setupPins(){
  pinMode(VIEW_BUTTON, INPUT_PULLUP);
  pinMode(SET_MINUTE_BUTTON, INPUT_PULLUP);
  pinMode(SET_HOUR_BUTTON, INPUT_PULLUP);
  pinMode(ENABLE_ALARM_SWITCH, INPUT_PULLUP);
  pinMode(SNOOZE_BUTTON, INPUT_PULLUP);
  pinMode(VOICE_RX, INPUT);
  pinMode(VOICE_TX, OUTPUT);
}

void initVoice(){
  voiceSerial.begin(9600);
  voiceSerial.print('\n');             // Send a CR in case the system is already up
  voiceSerial.print("N8");
  voiceSerial.print("\n");
  while (voiceSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  voiceSerial.flush();                 // Flush the receive buffer
}

void initRtc(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  //  rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

void handleAlarmEnabledSwitch(){
  alarm->setAlarmEnabled(digitalRead(ENABLE_ALARM_SWITCH)==HIGH ? true : false);
}
