#pragma once

#include <cmath>

#include "constants_and_utilities.h"

/**
 * class representing a 3D vector
 */
class vec3 {
  public:
    /**
     * Default Constructor - Sets all values to 0
     */
    vec3();

    /**
     * Constructor that initializes values to provided values
     * 
     * @param value1 double to assign to the x (first) value
     * @param value2 double to assign to the y (second) value
     * @param value3 double to assign to the z (third) value
     */
    vec3(double value1, double value2, double value3);

    /**
     * Returns the x value(first value)
     * 
     * @return double representing the x value (first value)
     */
    double x() const;

    /**
     * Returns the y value (second value)
     * 
     * @return double representing the y value (second value)
     */
    double y() const;

    /**
     * Returns the z value (third value)
     * 
     * @return double representing the z value (third value)
     */
    double z() const;

    /**
     * Overloaded Unary Minus Operator
     * 
     * @return a vec3 with all stored values multiplied by -1
     */
    vec3 operator-() const;

    /**
     * Overloaded Subscript Operator
     * 
     * @param i int representing the index in data_ to get the value of
     * @return double representing the value stored in the given index of data_
     * @throws out_of_range_error for values not 0-2
     */
    double operator[](int i) const;

    /**
     * Overloaded Addition Assignment Operator
     * Adds the vectors by the following procedure for each value in data_: 
     *   x_new = x_current + other_x
     * 
     * @param kToAdd constant reference to a vec3 to add to this vec3
     * @return a reference to this vec3 after the addition
     */
    vec3& operator+=(const vec3& kToAdd);

    /**
     * Overloaded Multiplication Assignment Operator
     * Multiplies each member of data_ by the given scalar multiple
     * 
     * @param kScalarMultiple constant double representing the scalar to multiply each 
     *     member of data_ by
     * @return a reference to this vec3 after the multiplications
     */
    vec3& operator*=(const double kScalarMultiple);

    /**
     * Overloaded Division Assignment Operator
     * Divides each member of data_ the given divisor
     * 
     * @param kDivisor constant double representing the scalar to divide each
     *     member of data_ by
     * @return a reference to this vec3 after the divisions
     */
    vec3& operator/=(const double kDivisor);

    /**
     * Get the length of the vector
     * 
     * @return a double representing the length of the vector
     */
    double length() const;

    /**
     * Get the length of the vector squared
     * 
     * @return a double representing the lenght of the vector squared
     */
    double lengthSquared() const;

    /**
     * Returns true if the vector is close to 0 in all directions
     * 
     * @return true if the vector is close to 0 in all directions and false otherwise
     */
    bool nearZero() const;

  private:
    /**
     * Array of doubles storing the data in the vec3
     * Index 0 stores the x (first) value
     * Index 1 stores the y (second) value
     * Index 2 stores the z (third) value
     */
    double data_[3];
    
    // size_t storing the index in data_ of the x (first) value
    size_t x_index_ = 0;

    // size_t storing the index in data_ of the y (second) value
    size_t y_index_ = 1;

    // size_t storing the index in data_ of the z (third) value
    size_t z_index_ = 2;
};

// Type aliases for vec3 (point3 and color)
using point3 = vec3;
using color = vec3;

// Vec3 Utility Functinons
/**
 * Overloaded OStream Operator
 * Adds the values of the given vector into the given stream
 * 
 * @param stream reference to a stream to add the values of the vector to
 * @param kVectorToPrint constant reference to a vec3 to add the values from
 * @return a reference to the given stream with the values of the given vector added to it
 */
inline std::ostream& operator<<(std::ostream& stream, const vec3& kVectorToPrint);

/**
 * Overloaded Adition Operator
 * Adds the given vectors by the following procedure for each value in data_: 
 *   x_new = x_vectorOne + x_vectorTwo
 * 
 * @param kVectorOne constant reference to the first vector to add
 * @param kVectorTwo constant reference to the second vector to add
 * @return a vec3 that is the result of the addition of the given vectors 
 */
inline vec3 operator+(const vec3& kVectorOne, const vec3& kVectorTwo);

/**
 * Overloaded Subtraction Operator 
 * Subtracts the second vector from the first vector by the following 
 * procedure for each value in data_:
 *   x_new = vector_x - toSubtract_x
 * 
 * @param kVector constant reference to a vector to subtract from 
 * @param kToSubtract constant reference to a vector to subtract from 
 *     kVector
 * @return a vec3 that is the result of the subtraction of the second vector
 *     from the first
 */
inline vec3 operator-(const vec3& kVector, const vec3& kToSubtract);

/**
 * Overloaded Multiplication Operator
 * Multiplies the given vectors by the following procedure for each value in data_: 
 *   x_new = x_current * other_x
 * 
 * @param kVectorOne constant reference to the first vector to multiply
 * @param kVectorTwo constant reference to the second vector to multiply
 * @return a vec3 that is the result of the multiplication of the given vectors 
 */
inline vec3 operator*(const vec3& kVectorOne, const vec3& kVectorTwo);

/**
 * Overloaded Multiplication Operator
 * Multiplies each member of data_ of the given vectorby the given scalar multiple
 * 
 * @param kVector constant reference to the vec3 to scale
 * @param kScalarMultiple constant double representing the scalar to multiply each 
 *     member of data_ in the given vector by
 * @return a vec3 that is the result of the scalar multiplication
 */
inline vec3 operator*(const vec3& kVector, const double kScalarMultiple);

/**
 * Overloaded Division Operator
 * Divides each member of data_ in the given vector by the divisor
 * 
 * @param kVector constant reference to the vec3 to scale
 * @param kDivisor constant double representing the scalar to divide each
 *     member of data_ in the given vector by
 * @return a vec3 that is the result of the scalar division
 */
inline vec3 operator/(const vec3& kVector, const double kDivisor);

/**
 * Returns the dot product of the given vectors
 * 
 * @param kVectorOne constant reference to the first vector to dot 
 * @param kVectorTwo constant reference to the second vector to dot
 * @return a double representing the dot product of the given vectors
 */
inline double dot(const vec3& kVectorOne, const vec3& kVectorTwo);

/**
 * Returns the cross product of the given vectors
 * 
 * @param kVectorOne constant reference to the first vector in the cross product
 * @param kVectorTwo constant reference to the second vector in the cross product
 * @return a vec3 representing the cross product of the given vectors
 */
inline vec3 cross(const vec3& kVectorOne, const vec3& kVectorTwo);

/**
 * Returns the unit vector of the given vector
 * 
 * @param vector vec3 to normalize
 * @retunr a vec3 representing the unit vector of the given vector
 */
inline vec3 unitVector(vec3 vector);

/**
 * Adds the given color's [0, 255] values to the given stream
 * Accounts for Antialiasing Sampling
 * 
 * @param stream a reference to a stream to add the given color's [0,255]
 *     values to
 * @param pixel_color a color to add it's [0, 255] values to the given stream
 * @param num_samples double representing the number of samples taken for the 
 *     pixel color
 */
void writeColor(std::ostream& stream, color pixel_color, double num_samples);

/**
 * Returns a random vector
 * 
 * @return a random vector where x, y, and z components are 
 *     in range [0, 1)
 */
inline vec3 randomVector();

/**
 * Returns a random vector where x, y, and z components are in
 * range [min, max)
 * 
 * @param min the minimum (inclusive) value for the x, y,
 *     and z componnets
 * @param max the maximum (non-inclusive) value for the x, y
 *     and z components
 * @return a random vector where x, y, and z components are in
 *     the range [min, max)
 */
inline vec3 randomVector(double min, double max);

/**
 * Returns a random point in the unit sphere
 * 
 * @return a point3 representing a random point in the unit sphere
 */
inline point3 randomPointInUnitSphere();

/**
 * Returns a random unit vector
 * 
 * @return a vec3 representing a random unit vector
 */
vec3 randomUnitVector();

/**
 * Computes the the reflected ray of the given ray off of a surface with the given surface normal
 * 
 * @param kRayToReflect a constant reference to a vec3 representing the ray to be reflected
 * @param kNormal a constant reference to a vec3 representing the surface normal of the surface
 *     that the given ray is reflected off of
 * @return a vec3 representing the reflected ray of the given ray off of a surface
 *     with the given surface normal
 */
vec3 reflect(const vec3& kRayToReflect, const vec3& kNormal);

/**
 * Computes the refracted ray of the given ray with a surface with the given surface normal
 * and the given value of 𝜂/𝜂'
 * 
 * @param kRayToRefract a constant reference to a vec3 representing the ray to be refracted
 * @param kNormal a constant reference to a vec3 representing the surface normal of the surface for
 *     the given ray to refract with
 * @param kEtaIntialOverEtaFinal a constant double representing the value of 𝜂/𝜂' for the refraction
 * @return a vec3 representing the refracted ray of the given ray with a surface with the given
 *     surface normal and the given value of 𝜂/𝜂'
 */
vec3 refract(const vec3& kRayToRefract, const vec3& kNormal, const double kEtaIntialOverEtaFinal);
