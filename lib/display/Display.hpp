#include "Adafruit_LEDBackpack.h"

class Display {
  public:
    Display();
    void setDisplay(Clock* clock, bool alarmEnabled);
    void writeDisplay();
  private:
    Adafruit_7segment m_matrix;
};
