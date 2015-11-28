// Device driver for an angular pointer mounted on a servo
#pragma once

#include "application.h"
#include "angle_movable.h"
#include <vector>

class PointerObserver {
  public:
    virtual void angleChanged(int angle) = 0;
};

class Pointer : public AngleMovable {
  public:
    Pointer(int pin);
    void moveToAngle(int angle);
    bool isMoving();
    void setInitialAngle(int angle);

    void addObserver(PointerObserver *observer);

  private:
    void startServo();
    void updateServo();
    void updatePositionActual();
    void stopServo();
    void notifyObservers();

    static const int RATE = 1;
    int pin;
    bool moving;
    int positionActual;
    int positionDesired;
    std::vector<PointerObserver*> observers;

    Servo servo;

    class ServoTimer: public Timer {
      public:
        static const unsigned PERIOD = 40; /* ms */
        ServoTimer(Pointer &pointer);
        void timeout() override;


      private:
        Pointer &pointer;
    };

    ServoTimer timer;
};
