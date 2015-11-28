// Map the angle of clothes on the poster
#include "weather_pointer.h"

#include <algorithm>

const WeatherPointer::ClothesAngles WeatherPointer::clothesAngles = {
  { "umbrella", 167 },
  { "jacket", 137 },
  { "tshirt", 113 },
  { "sweater", 83 },
  { "hat", 55 },
  { "shovel", 30 }
};

WeatherPointer::WeatherPointer(AngleMovable &movable)
  : movable(movable) {
}

void WeatherPointer::pointTo(const String &clothes) {
  int angle = findClothesAngle(clothes);
  if(angle >= 0) {
    movable.moveToAngle(angle);
  }
}

int WeatherPointer::findClothesAngle(const String &clothes) {
  auto it = std::find_if(clothesAngles.begin(), clothesAngles.end(),
      [clothes] (WeatherPointer::ClothesAngle pair) {
      return pair.first == clothes;
      }
      );

  int angle = -1;
  if(it != clothesAngles.end()) {
    angle = it->second;
  }
  return angle;
}
