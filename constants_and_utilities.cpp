#include "constants_and_utilities.h"

inline double randomDouble() {
  static std::uniform_real_distribution<double> random_distribution 
      = std::uniform_real_distribution<double>(0.0, 1.0);
  static std::mt19937 random_generator;
  return random_distribution(random_generator);
}

inline double clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  }
  return value;
}
