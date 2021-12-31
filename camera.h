#pragma once

#include "ray.h"
#include "vec3.h"

/**
 * Class that manages the virual camera and tasks for scene sampling
 */
class camera {
  public:
    /**
     * Constructor that creates a camera and sets up the scene viewport
     * The focal length is 1.0 and the aspect ratio is 16/9
     * Viewport height is set to 2.0 and origin (camera location) is (0, 0, 0)
     */
    camera();
    
    /**
     * Returns the ray from the camera to the pixel in the viewport corresponding to 
     * the given horizontal and vertical shifts from the origin  
     * 
     * @param horizontal_factor factor by which to shift the pixel horizontally
     * @param vertical_factor factor by which to shift the pixel vertically
     * @return ray representing the ray from the camera to the pixel in the viewport
     *     corresponding to the given horizontal and vertical shifts from the origin
     */
    ray getRay(double horizontal_factor, double vertical_factor) const;

  private:
    // point3 representing the location of the camera
    point3 origin_;
    // point3 representing the lower left corner of the viewport
    point3 lower_left_corner_;
    // vec3 representing the horizontal direction of the viewport
    vec3 horizontal_direction_;
    // vec3 representing the vertical direction of the viewport
    vec3 vertical_direction_;
};
