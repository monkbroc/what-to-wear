// Main file for the Weather clothes clock
#include "weather_pointer.h"
#include "pointer.h"
#include "persistence.h"
#include "pointer_persistence.h"
#include "power_supply.h"

SYSTEM_THREAD(ENABLED);

Pointer pointer(D0);
WeatherPointer weatherPointer(pointer);
Persistence persistence;
PointerPersistence pointerPersistence(pointer, persistence);
PowerSupply powerSupply;

const int CONNECT_DELAY_SECS = 30;
const int SLEEP_DELAY_SECS = 60;
const int SLEEP_TIME_SECS = 60 * 60;

bool responseReceived = false;
unsigned long sleepTimer = 0;

int setClothes(String value) {
  sleepTimer = millis();
  weatherPointer.pointTo(value);
  return 0;
}

void setClothesHook(const char *event, const char *value) {
  String clothes = String(value).trim();
  // When clothes selection is manual, wait for the "clothes" cloud
  // function to be called to move the pointer
  if(clothes != "manual") {
    responseReceived = true;
    setClothes(clothes);
  }
}

void goToSleep() {
  System.sleep(SLEEP_MODE_DEEP, SLEEP_TIME_SECS);
}

void setup() {
  powerSupply.setup();

  pointerPersistence.setup();
  Particle.subscribe("hook-response/what-to-wear", setClothesHook, MY_DEVICES);
  Particle.function("clothes", setClothes);

  if(waitFor(Particle.connected, CONNECT_DELAY_SECS * 1000)) {
    Particle.publish("what-to-wear", PRIVATE);
  } else {
    goToSleep();
  }
  sleepTimer = millis();
}

bool readyToSleep() {
  if(responseReceived && !pointer.isMoving()) {
    return true;
  }

  return ((millis() - sleepTimer) > SLEEP_DELAY_SECS * 1000);
}

void loop() {
  if(readyToSleep()) {
    goToSleep();
  }
}
