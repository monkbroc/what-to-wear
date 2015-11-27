// Device driver for an angular pointer mounted on a servo
#pragma once

#include "application.h"
#include "angle_movable.h"

class Pointer : public AngleMovable {
    public:
    Pointer(int pin);
    void moveToAngle(int angle);
    
    bool isMoving();


    private:
    void startServo();
    void updateServo();
    void updatePositionActual();
    void stopServo();
    
    static const int RATE = 1;
    int pin;
    bool moving;
    int positionActual;
    int positionDesired;
    
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
