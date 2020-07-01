// Save last position in EEPROM
#pragma once

class Persistence {
  public:
    int loadPosition();
    void savePosition(int angle);

  private:
    static const int POSITION_ADDR;
};
