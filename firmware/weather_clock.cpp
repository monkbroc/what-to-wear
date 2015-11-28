// Main file for the Weather clothes clock
#include "weather_pointer.h"
#include "pointer.h"
#include "persistence.h"
#include "pointer_persistence.h"

Pointer pointer(D0);
WeatherPointer weatherPointer(pointer);
Persistence persistence;
PointerPersistence pointerPersistence(pointer, persistence);

int setClothes(String value) {
  weatherPointer.pointTo(value);
  return 0;
}

void setup() {
  pointerPersistence.setup();
  Particle.function("clothes", setClothes);
}

void loop() {

}
