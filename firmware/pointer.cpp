// Device driver for an angular pointer mounted on a servo
#include "pointer.h"
#include <algorithm>

Pointer::Pointer(int pin)
  : pin(pin), timer(*this) {
}

void Pointer::moveToAngle(int angle) {
  {
    CriticalSection cs;
    if(positionDesired == angle) {
      return;
    }

    positionDesired = angle;

    if(!isMoving()) {
      startServo();
      timer.start();
    }
  }
  notifyObservers();
}

bool Pointer::isMoving() {
  return moving;
}

void Pointer::setInitialAngle(int angle) {
  positionActual = angle;
}

void Pointer::startServo() {
  servo.attach(pin);
  moving = true;
}

void Pointer::updateServo() {
  if(positionDesired == positionActual) {
    stopServo();
    timer.stop();
    return;
  }

  updatePositionActual();
  servo.write(positionActual);
}

void Pointer::updatePositionActual() {
  int deltaPosition = max(min(positionDesired - positionActual, RATE), -RATE);
  positionActual += deltaPosition;
}

void Pointer::stopServo() {
  servo.detach();
  moving = false;
}

void Pointer::addObserver(PointerObserver *observer) {
  observers.push_back(observer);
}

void Pointer::notifyObservers() {
  std::for_each(observers.begin(), observers.end(), [this](PointerObserver *observer) {
    observer->angleChanged(positionDesired);
  });
}

Pointer::ServoTimer::ServoTimer(Pointer &pointer)
  : Timer(ServoTimer::PERIOD, Timer::timer_callback_fn(nullptr)),
  pointer(pointer) {
}

void Pointer::ServoTimer::timeout() {
  pointer.updateServo();
}
