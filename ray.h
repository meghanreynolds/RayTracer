#pragma once

#include "vec3.h"

/**
 * Class representing a Ray
 */
class ray {
  public:
    /**
     * Default Constructor
     * Sets origin and direction to zero vectors
     */
    ray();

    /**
     * Constructor sets origin_ to the given origin and
     * direction_ to the given direction
     * 
     * @param origin constant reference to a point3 representing the ray's origin
     * @param direction constant reference to vec3 representing the ray's direction
     */
    ray(const point3& origin, const vec3& direction);

    /**
     * Returns the ray's origin
     * 
     * @return a point3 representing the ray's origin
     */
    point3 origin() const;

    /**
     * Returns the ray's direction vector
     * 
     * @return  vec3 representing the ray's direction vector
     */
    vec3 direction() const;

    /**
     * Calculates the position along the ray at the given t value
     * 
     * @param t a double representing the t value to get the position at
     * @return a point3 representing the position along the ray at the given t value
     */ 
    point3 at(double t) const;

  private:
    // point3 storing the ray's origin
    point3 origin_;
    
    // vec3 storing the ray's direction vector
    vec3 direction_;
};
