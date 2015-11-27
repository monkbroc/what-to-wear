// Main file for the Weather clothes clock
#include "weather_pointer.h"
#include "pointer.h"

Pointer pointer(D0);
WeatherPointer weatherPointer(pointer);

int setClothes(String value) {
    weatherPointer.pointTo(value);
    return 0;
}

void setup() {
    Particle.function("clothes", setClothes);
}

void loop() {

}

