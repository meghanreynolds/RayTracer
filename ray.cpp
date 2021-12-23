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

bool sphereWasHit(const point3& kSphereCenter, double radius, const ray& kRay) {
  const vec3 kRayDirection = kRay.direction();
  const vec3 kDifference = kRay.origin() - kSphereCenter;
  // a, b, and c values in the quadratic equation given by the expanded vector form of a sphere
  // using P = ray equation
  const double kA = dot(kRayDirection, kRayDirection);
  const double kB = dot(kRayDirection, kDifference) * 2;
  const double kC = dot(kDifference, kDifference) - (radius * radius);

  const double kDiscriminant = (kB * kB) - (4 * kA * kC);
  // if discriminant < 0, there are no real solutions to the quadratic therefore the sphere 
  // could not have been hit
  if (kDiscriminant < 0) {
    return false;
  } else {
    return true;
  }
}

color rayColor(const ray& kRay) {
  // first check if the ray hits the sphere (color pixel red if so)
  const point3 kSphereCenter = point3(0, 0, -1);
  const double kSphereRadius = 0.5;
  const color kRed = color(1, 0, 0);
  if (sphereWasHit(kSphereCenter, kSphereRadius, kRay)) {
    return kRed;
  }

  // otherwise ray is through background (blue-white gradient) pixel
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
