#include "camera.h"

camera::camera() {
  const double kAspectRatio = 16.0 / 9.0;
  const double kViewportHeight = 2.0;
  const double kViewportWidth = kAspectRatio * kViewportHeight;
  const double kFocalLength = 1.0;

  origin_ = point3(); // point3 defaults to be the zero vector
  horizontal_direction_ = vec3(kViewportWidth, 0, 0);
  vertical_direction_ = vec3(0, kViewportHeight, 0);
  lower_left_corner_ = origin_ - (horizontal_direction_ / 2) - (vertical_direction_ / 2)
    - vec3(0, 0, kFocalLength);
}

ray camera::getRay(double horizontal_factor, double vertical_factor) const {
  // direction of ray from the origin to the pixel corresponding to the given vertical and 
  // horizontal shifts in the viewport
  const vec3 kRayDirection = lower_left_corner_ + (horizontal_direction_ * horizontal_factor) 
    + (vertical_direction_ * vertical_factor) - origin_;
  return ray(origin_, kRayDirection);
}
