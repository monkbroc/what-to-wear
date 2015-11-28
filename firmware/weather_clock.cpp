// Main file for the Weather clothes clock
#include "weather_pointer.h"
#include "pointer.h"
#include "persistence.h"
#include "pointer_persistence.h"

SYSTEM_THREAD(ENABLED);

Pointer pointer(D0);
WeatherPointer weatherPointer(pointer);
Persistence persistence;
PointerPersistence pointerPersistence(pointer, persistence);

const int CONNECT_DELAY_SECS = 30;
const int SLEEP_DELAY_SECS = 60;
const int SLEEP_TIME_SECS = 60 * 60;

bool responseReceived = false;

int setClothes(String value) {
  responseReceived = true;
  weatherPointer.pointTo(value);
  return 0;
}

void setClothesHook(const char *event, const char *value) {
  RGB.control(true);
  RGB.color(255, 128, 0);
  setClothes(String(value).trim());
}

void goToSleep() {
  System.sleep(SLEEP_MODE_DEEP, SLEEP_TIME_SECS);
}

void setup() {
  pointerPersistence.setup();
  Particle.subscribe("hook-response/what-to-wear", setClothesHook, MY_DEVICES);
  Particle.function("clothes", setClothes);

  if(waitFor(Particle.connected, CONNECT_DELAY_SECS * 1000)) {
    Particle.publish("what-to-wear", PRIVATE);
  } else {
    goToSleep();
  }
}

bool readyToSleep() {
  if(responseReceived && !pointer.isMoving()) {
    return true;
  }

  return (millis() > SLEEP_DELAY_SECS * 1000);
}

void loop() {
  if(readyToSleep()) {
    goToSleep();
  }
}
