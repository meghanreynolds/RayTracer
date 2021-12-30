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
