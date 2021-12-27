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

double hitSphere(const point3& kSphereCenter, double radius, const ray& kRay) {
  const vec3 kRayDirection = kRay.direction();
  const vec3 kDifference = kRay.origin() - kSphereCenter;
  // a, b, and c values in the quadratic equation given by the expanded vector form of a sphere
  // using P = ray equation
  const double kA = dot(kRayDirection, kRayDirection);
  const double kHalfB = dot(kRayDirection, kDifference);
  const double kC = dot(kDifference, kDifference) - (radius * radius);

  const double kDiscriminant = (kHalfB * kHalfB) - (kA * kC);
  // if discriminant < 0, there are no real solutions to the quadratic therefore the 
  // sphere could not have been hit
  if (kDiscriminant < 0) {
    return -1.0;
  } else {
    // we are looking for the closest point of intersection so we subtract the 
    // discriminant
    return ((-kHalfB - std::sqrt(kDiscriminant)) / (kA));
  }
}

color rayColor(const ray& kRay) {
  const point3 kSphereCenter = point3(0, 0, -1);
  const double kSphereRadius = 0.5;
  const color kRed = color(1, 0, 0);
  const double kT = hitSphere(kSphereCenter, kSphereRadius, kRay);
  // ensure the ray hits the sphere (t > 0) before visualizing surface normals
  if (kT > 0.0) {
    const vec3 kUnitSurfaceNormal = unitVector(kRay.at(kT) - kSphereCenter);
    // adding 1 to each component ensures each component >= 0 and 
    // multiplting by 0.5 ensures each component <= 1
    return color(kUnitSurfaceNormal.x() + 1, kUnitSurfaceNormal.y() + 1, 
        kUnitSurfaceNormal.z() + 1) * 0.5;
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
