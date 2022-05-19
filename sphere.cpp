#include "Hittable.h"
#include "sphere.h"

sphere::sphere(point3 center, double radius, std::shared_ptr<Material> material_ptr) : center_(center), 
    radius_(radius), material_ptr_(material_ptr) {}

bool sphere::wasHit(const ray& kRay, double min_t, double max_t, HitRecord& hit_record) const {
  const vec3 kRayDirection = kRay.direction();
  const vec3 kDifference = kRay.origin() - center_;
  // a, b, and c values in the quadratic equation given by the expanded vector form of a sphere
  // using P = ray equation
  const double kA = dot(kRayDirection, kRayDirection);
  const double kHalfB = dot(kRayDirection, kDifference);
  const double kC = dot(kDifference, kDifference) - (radius_ * radius_);

  const double kDiscriminant = (kHalfB * kHalfB) - (kA * kC);
  // if discriminant < 0, there are no real solutions to the quadratic therefore the 
  // sphere could not have been hit
  if (kDiscriminant < 0) {
    return false;
  } else {
    // we are looking for the closest point of intersection so we subtract the 
    // discriminant
    double root = ((-kHalfB - std::sqrt(kDiscriminant)) / (kA));
    if (root < min_t || root > max_t) {
      // test the other root if the closest root is out of the acceptable t range
      root = ((-kHalfB + std::sqrt(kDiscriminant)) / (kA));
      // if both roots are out of the acceptable t range, return false
      if (root < min_t || root > max_t) {
        return false;
      }
    }
    // root is now closest root within the acceptable t range
    // update hit record with obtained information
    hit_record.t_ = root;
    point3 point_of_intersection = kRay.at(root);
    hit_record.point_of_intersection_ = kRay.at(root);
    const vec3 kOutwardNormal = unitVector(point_of_intersection - center_);
    hit_record.setFaceNormal(kRay, kOutwardNormal);
    hit_record.material_pointer = material_ptr_;
    return true;
  }
}
