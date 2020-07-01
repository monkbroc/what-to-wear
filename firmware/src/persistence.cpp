// Save last position in EEPROM
#include "application.h"
#include "persistence.h"

const int Persistence::POSITION_ADDR = 0;

int Persistence::loadPosition() {
  int value = EEPROM.read(POSITION_ADDR);
  if(value == 0xFF) {
    return 0;
  } else {
    return value;
  }
}

void Persistence::savePosition(int angle) {
  EEPROM.write(POSITION_ADDR, angle);
}
