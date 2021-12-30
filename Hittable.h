#pragma once

#include "ray.h"
#include "vec3.h"

/**
 * Struct storing the point of intersection, surface normal, 
 * and t value of a ray hitting a hittable object
 */
struct HitRecord {
  // point3 representing the point of intersection of the ray and hittable object
  point3 point_of_intersection_;
  // vec3 representing the surface normal 
  vec3 surface_normal_;
  // double representing the t value at which the intersection occurs
  double t_;
  // bool that is true if the ray is front facing (insersects the hittable obect from the inside)
  bool front_facing_;

  /**
   * Sets the surface normal to always point against the direction of the ray and updates front_facing_
   * 
   * @param kRay constant reference to a ray to base the direction of the normal off of
   * @param kOutwardNormal constant reference to a vec3 representing the outward normal
   */
  inline void setFaceNormal(const ray& kRay, const vec3& kOutwardNormal) {
    // if the dot product of the ray and outward normal is positive, they point in the same general direction 
    // therefore the ray intersects the hittable object from the inside
    if (dot(kRay.direction(), kOutwardNormal) > 0) {
      surface_normal_ = kOutwardNormal * -1;
      front_facing_ = false;
    // otherwise, the ray and the outward normal point in the opposite general direction, therefore the ray 
    // intersects the hittable object from the outside
    } else {  
      surface_normal_ = kOutwardNormal;
      front_facing_ = true;
    }
  }
};

/**
 * Class representing a hittable object
 */
class Hittable {
  public:
    /**
     * Virtual Destructor that does nothing- for Derived Classes to Call
     */
    virtual ~Hittable() {}

    /**
     * Virtual Function that returns true if the hittable object was hit by the given ray 
     * in the given range of values for t
     * 
     * Updates the hit record with the closest point of intersection, corresponding t value, 
     * and the unit surface normal
     * 
     * NOTE: If not overridden, always returns false
     * 
     * @param kRay constant reference to the ray to check if it hits the 
     *     given hittable object
     * @param min_t double representing the minimum t value for the intersection
     * @param max_t double representing the maximum t value for the intersection
     * @param hit_record reference to a hit record to update with the details of the intersection of the ray
     *     and the hit object (not updated if not hit within the acceptable t value range)
     * @return true if the hittable object was hit by the given ray in the given range of values for t 
     *     and false otherwise
     */
    virtual bool wasHit(const ray& kRay, double min_t, double max_t, 
        HitRecord& hit_record) const = 0;
};
