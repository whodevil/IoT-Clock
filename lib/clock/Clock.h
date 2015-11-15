class Clock {
  public:
    Clock(int hour, int minute);
    int hour();
    int minute();
    bool isPm();
    bool equals(Clock* clock);
  protected:
    int m_hour;
    int m_minute;
    bool m_isPm;
};

class AlarmClock : public Clock {
  public:
    AlarmClock();
    void incrementHour();
    void incrementMinute();
    void snooze();
    void decrementSnoozeCounter();
    bool isAlarmRinging();
    void startAlarm();
    void stopAlarm();
    void setAlarmEnabled(bool alarmEnabled);
    bool alarmEnabled();

  private:
    int m_snoozeCounter;
    bool m_alarmEnabled;
    bool m_alarmRinging;
};

int formattedTime(Clock* clock);
