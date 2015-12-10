// Main file for the Weather clothes clock
#include "weather_pointer.h"
#include "pointer.h"
#include "persistence.h"
#include "pointer_persistence.h"
#include "power_supply.h"

SYSTEM_THREAD(ENABLED);

void goToSleep();

Pointer pointer(D0);
WeatherPointer weatherPointer(pointer);
Persistence persistence;
PointerPersistence pointerPersistence(pointer, persistence);
PowerSupply powerSupply;

const int CONNECT_DELAY_SECS = 30;
const int SLEEP_DELAY_SECS = 2 * 60;
const int SLEEP_TIME_SECS = 60 * 60;

bool manualMode = false;
bool hookResponseReceived = false;
unsigned long lastResponseTime = 0;

bool wokeUpFromPin() {
  pinMode(WKP, INPUT);
  return digitalRead(WKP) == HIGH;
}

STARTUP(manualMode = wokeUpFromPin());

int setClothes(String value) {
  Serial.println("Setting clothes " + value);
  lastResponseTime = millis();
  weatherPointer.pointTo(value);
  return 0;
}

void setClothesFromHook(const char *event, const char *value) {
  String clothes = String(value).trim();
  Serial.println("Received what-to-wear response");
  hookResponseReceived = true;
  setClothes(clothes);
}

void getClothesFromHook() {
  Particle.subscribe("hook-response/what-to-wear", setClothesFromHook, MY_DEVICES);
  if(waitFor(Particle.connected, CONNECT_DELAY_SECS * 1000)) {
    Serial.println("Published what-to-wear event");
    Particle.publish("what-to-wear", PRIVATE);
  } else {
    Serial.println("Couldn't connect => Go to sleep");
    goToSleep();
  }
}

void setup() {
  Serial.begin(9600); delay(200);

  powerSupply.setup();
  Serial.println("Woke from " + String(manualMode ? "pin" : "timer/reset"));

  pointerPersistence.setup();
  Particle.function("clothes", setClothes);

  if(!manualMode) {
    getClothesFromHook();
  }
}

unsigned long timeSinceLastResponse() {
  return millis() - lastResponseTime;
}

bool readyToSleep() {
  if(hookResponseReceived && !pointer.isMoving()) {
    return true;
  }

  return timeSinceLastResponse() > SLEEP_DELAY_SECS * 1000;
}

void loop() {
  if(readyToSleep()) {
    Serial.println("Done waiting => Go to sleep"); delay(200);
    goToSleep();
  }
}

void goToSleep() {
  System.sleep(SLEEP_MODE_DEEP, SLEEP_TIME_SECS);
}

