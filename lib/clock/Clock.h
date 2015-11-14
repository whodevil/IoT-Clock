class Clock {
  public:
    Clock(int hour, int minute);
    int hour();
    int minute();
    bool isPm();
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
};

int formattedTime(Clock* clock);
