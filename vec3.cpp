#include "vec3.h"

vec3::vec3() {
  data_[kXIndex] = 0.0;
  data_[kYIndex] = 0.0;
  data_[kZIndex] = 0.0;
}

vec3::vec3(double value1, double value2, double value3) {
  data_[kXIndex] = value1;
  data_[kYIndex] = value2;
  data_[kZIndex] = value3;
}

double vec3::x() const {
  return data_[kXIndex];
}

double vec3::y() const {
  return data_[kYIndex];
}

double vec3::z() const {
  return data_[kZIndex];
}

vec3 vec3::operator-() const {
  return vec3(-1 * data_[kXIndex], -1 * data_[kYIndex], -1 * data_[kZIndex]);
}

double vec3::operator[](int i) const {
  return data_[i];
}

vec3& vec3::operator+=(const vec3& kToAdd) {
  data_[kXIndex] += kToAdd.x();
  data_[kYIndex] += kToAdd.y();
  data_[kZIndex] += kToAdd.z();
  return *this;
}

vec3& vec3::operator*=(const double kScalarMultiple) {
  data_[kXIndex] *= kScalarMultiple;
  data_[kYIndex] *= kScalarMultiple;
  data_[kZIndex] *= kScalarMultiple;
  return *this;
}

vec3& vec3::operator/=(const double kDivisor) {
  *this *= (1 / kDivisor);
  return *this;
}

double vec3::length() const {
  return std::sqrt(lengthSquared());
}

double vec3::lengthSquared() const {
  return (data_[kXIndex] * data_[kXIndex]) + (data_[kYIndex] * data_[kYIndex]) + (data_[kZIndex] * data_[kZIndex]);
}

inline std::ostream& operator<<(std::ostream& stream, const vec3& kVectorToPrint) {
  stream << kVectorToPrint.x() << ' ' << kVectorToPrint.y() << ' ' << kVectorToPrint.z();
  return stream;
}

inline vec3 operator+(const vec3& kVectorOne, const vec3& kVectorTwo) {
  return vec3(kVectorOne.x() + kVectorTwo.x(), kVectorOne.y() + kVectorTwo.y(), kVectorOne.z() + kVectorTwo.z());
}

inline vec3 operator-(const vec3& kVector, const vec3& kToSubtract) {
  return vec3(kVector.x() - kToSubtract.x(), kVector.y() - kToSubtract.y(), kVector.z() - kToSubtract.z());
}

inline vec3 operator*(const vec3& kVectorOne, const vec3& kVectorTwo) {
  return vec3(kVectorOne.x() * kVectorTwo.x(), kVectorOne.y() * kVectorTwo.y(), kVectorOne.z() * kVectorTwo.z());
}

inline vec3 operator*(const vec3& kVector, const double kScalarMultiple) {
  return vec3(kVector.x() * kScalarMultiple, kVector.y() * kScalarMultiple, kVector.z() * kScalarMultiple);
}

inline vec3 operator/(const vec3& kVector, const double kDivisor) {
  return kVector * (1 / kDivisor);
}

inline double dot(const vec3& kVectorOne, const vec3& kVectorTwo) {
  // overloaded multiplication operator multiplies component-wise
  vec3 multiplied = kVectorOne * kVectorTwo;
  return multiplied.x() + multiplied.y() + multiplied.z();
}

inline vec3 cross(const vec3& kVectorOne, const vec3& kVectorTwo) {
  return vec3((kVectorOne.y() * kVectorTwo.z()) - (kVectorOne.z() - kVectorTwo.y()),
      (kVectorTwo.x() * kVectorOne.z()) - (kVectorOne.x() * kVectorTwo.z()), 
      (kVectorOne.x() * kVectorTwo.y()) - (kVectorOne.y() * kVectorTwo.x()));
}

inline vec3 unitVector(vec3 vector) {
  return vector / vector.length();
}

void writeColor(std::ostream& stream, color pixel_color) {
  stream << static_cast<int>(255.999 * pixel_color.x()) << ' ' 
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
