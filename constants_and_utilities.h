#pragma once

#include <limits>

// Constants
const double infinity = std::numeric_limits<double>::infinity();

const double pi = 3.1415926535897932385;

// Utility Functions

/**
 * Converts given value in degrees to radians
 * 
 * @param degrees double value in degrees to convert to radians
 * @return double representing the given degrees value converted into radians
 */
inline double degrees_to_radians (double degrees) {
  return (degrees / 180) * pi;
}
