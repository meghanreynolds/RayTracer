#include "ray.h"

ray::ray(const point3& origin, const vec3& direction) : origin_(origin), 
    direction_(direction) {}

point3 ray::origin() const {
  return origin_;
}

vec3 ray::direction() const {
  return direction_;
}

point3 ray::at(double t) const {
  return origin_ + (direction_ * t);
}

color rayColor(const ray& kRay) {
  const vec3 kUnitVector = unitVector(kRay.direction());
  // midpoint of unit y component and 1.0 (ensures 0 <= t <= 1)
  const double t = 0.5 * (kUnitVector.y() + 1.0);
  // starting color for the lerp
  const color kWhite = color(1, 1, 1);
  // ending color for the lerp
  const color kLightBlue = color(0.5, 0.7, 1.0);
  // lerp white and light blue based on t
  return (kWhite * (1.0 - t)) + (kLightBlue * t);
}
