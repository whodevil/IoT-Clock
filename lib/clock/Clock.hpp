class Clock {
  public:
    Clock(const int hour, const int minute);
    virtual ~Clock(){}; //this is important because subclassed
    int hour() const; //contract that says I'm not changing the state
                      //of the clock object I'm calling it on
    int minute() const;
    bool isPm() const;
    bool hasSameTime(const Clock& clock) const;
  protected:
    int hour_;//this is tripwire coding standard
    int minute_;
    bool isPm_;
};

class AlarmClock : public Clock {
  public:
    AlarmClock() : Clock(6,50), snoozeCounter_(0), alarmEnabled_(false), alarmRinging_(false) {};
    void incrementHour();
    void incrementMinute();
    void snooze();
    void decrementSnoozeCounter();
    bool isAlarmRinging() const;
    void startAlarm();
    void stopAlarm();
    void setAlarmEnabled(bool alarmEnabled);
    bool alarmEnabled() const;

  private:
    int snoozeCounter_;
    bool alarmEnabled_;
    bool alarmRinging_;
};

int formattedTime(const Clock& clock);
