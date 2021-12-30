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
