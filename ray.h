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

// Utility Functions for Rays

/**
 * This functions determines whether or not the sphere with the given center
 * and radius was hit by the given ray
 * 
 * @param kSphereCenter constant reference to a point3 representing the center of the sphere
 * @param radius double representing the radius of the Sphere
 * @param kRay constant reference to the ray to check if it hits the given sphere
 * @return a bool that is true if the given ray hits the given sphere and false otherwise
 */
bool sphereWasHit(const point3& kSphereCenter, double radius, const ray& kRay);

/**
 * This function finds the color of the pixel the ray passes through
 * 
 * @param kRay constant reference to a ray to determine the pixel color for
 * @return a color determined by the scene in front of the camera
 */
color rayColor(const ray& kRay);