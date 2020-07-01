// Map the angle of clothes on the poster
#pragma once

#include <vector>
#include <utility>

#include "application.h"
#include "angle_movable.h"

class WeatherPointer {
  public:
    WeatherPointer(AngleMovable &movable);
    void pointTo(const String &clothes);

  private:
    typedef std::pair<String, int> ClothesAngle;
    typedef std::vector<ClothesAngle> ClothesAngles;
    static const ClothesAngles clothesAngles;

    int findClothesAngle(const String &clothes);

    AngleMovable &movable;
};
