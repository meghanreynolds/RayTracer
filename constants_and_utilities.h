#pragma once

#include <limits>
#include <random>

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
inline double degrees_to_radians(double degrees) {
  return (degrees / 180) * pi;
}

/**
 * Returns random real number in range [0,1)
 * 
 * @return double representing a random real in range [0,1)
 */
inline double random_double() {
  static std::uniform_real_distribution<double> random_distribution 
      = std::uniform_real_distribution<double>(0.0, 1.0);
  static std::mt19937 random_generator;
  return random_distribution(random_generator);
}

/**
 * Returns random real number in range [min, max)
 * 
 * @param min the minimum (inclusive) value for the random real
 * @param max the maximum (non-inclusive) value for the random real
 * @return double representing a random real in range [min, max)
 */
inline double random_double(double min, double max) {
  return min + (random_double() * (max - min));
}

/**
 * Function that ensures given value falls within [min, max] by changing
 * values < min to min and values > max to max
 * 
 * @param value the value to ensure that it falls within the given inclusive range
 * @param min the minimum (inclusive) value for the given value
 * @param max the maximum (inclusive) value for the given value
 * @return the value modified to be within the given inclusive range
 *     if < min, reuturns min; if > max returns max; otherwise returns 
 *     the given value
 */
inline double clamp (double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  }
  return value;
}
