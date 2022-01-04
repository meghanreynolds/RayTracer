#include "vec3.h"

vec3::vec3() {
  data_[x_index_] = 0.0;
  data_[y_index_] = 0.0;
  data_[z_index_] = 0.0;
}

vec3::vec3(double value1, double value2, double value3) {
  data_[x_index_] = value1;
  data_[y_index_] = value2;
  data_[z_index_] = value3;
}

double vec3::x() const {
  return data_[x_index_];
}

double vec3::y() const {
  return data_[y_index_];
}

double vec3::z() const {
  return data_[z_index_];
}

vec3 vec3::operator-() const {
  return vec3(-1 * data_[x_index_], -1 * data_[y_index_], -1 * data_[z_index_]);
}

double vec3::operator[](int i) const {
  return data_[i];
}

vec3& vec3::operator+=(const vec3& kToAdd) {
  data_[x_index_] += kToAdd.x();
  data_[y_index_] += kToAdd.y();
  data_[z_index_] += kToAdd.z();
  return *this;
}

vec3& vec3::operator*=(const double kScalarMultiple) {
  data_[x_index_] *= kScalarMultiple;
  data_[y_index_] *= kScalarMultiple;
  data_[z_index_] *= kScalarMultiple;
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
  return (data_[x_index_] * data_[x_index_]) + (data_[y_index_] * data_[y_index_]) + (data_[z_index_] * data_[z_index_]);
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

void writeColor(std::ostream& stream, color pixel_color, double num_samples) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // account for antialiasing sampling and gamma-correct for gamma = 2.0
  r =  std::sqrt(r / num_samples);
  g =  std::sqrt(g / num_samples);
  b =  std::sqrt(b / num_samples);

  stream << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' 
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

inline vec3 randomVector() {
  return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline vec3 randomVector(double min, double max) {
  return vec3(randomDouble(min, max), randomDouble(min, max), 
      randomDouble(min, max));
}

inline point3 randomPointInUnitSphere() {
  while (true) {
    const point3 kRandomPoint = randomVector(-1, 1);
    if (kRandomPoint.lengthSquared() < 1) {
      return kRandomPoint;
    }
  }
}

vec3 randomUnitVector() {
  return unitVector(randomPointInUnitSphere());
}
