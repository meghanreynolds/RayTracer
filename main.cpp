#include <iostream>
#include <fstream>
#include <string>

#include "Hittable.h"
#include "ray.h"
#include "ray.cpp"
#include "sphere.h"
#include "sphere.cpp"
#include "vec3.h"
#include "vec3.cpp"



color rayColor(const ray& kRay) {
  const point3 kSphereCenter = point3(0, 0, -1);
  const double kSphereRadius = 0.5;
  const sphere kSphere = sphere(kSphereCenter, kSphereRadius);
  const color kRed = color(1, 0, 0);
  HitRecord sphere_hit_record = HitRecord();
  const bool kWasHit = kSphere.wasHit(kRay, 0, 1, sphere_hit_record);
  const double kT = sphere_hit_record.t_;
  // ensure the ray hits the sphere before visualizing surface normals
  if (kWasHit) {
    const vec3 kUnitSurfaceNormal = sphere_hit_record.surface_normal_;
    // adding 1 to each component ensures each component >= 0 and 
    // multiplting by 0.5 ensures each component <= 1
    return color(kUnitSurfaceNormal.x() + 1, kUnitSurfaceNormal.y() + 1, 
        kUnitSurfaceNormal.z() + 1) * 0.5;
  }

  // otherwise ray is through background (blue-white gradient) pixel
  const vec3 kUnitVector = unitVector(kRay.direction());
  // midpoint of unit y component and 1.0 (ensures 0 <= t <= 1)
  const double t = 0.5 * (kUnitVector.y() + 1.0);
  // starting color for the lerp
  const color kWhite = color(1, 1, 1);
  // ending color for the lerp
  const color kLightBlue = color(0.5, 0.7, 1.0);
  // lerp white and light blue based on t
  return (kWhite * (1.0 - t)) + (kLightBlue * t);
}

void basicSphere(std::string file_name) {
  std::ofstream image_file = std::ofstream(file_name, std::ios::ate);
  if (image_file.is_open()){
    // P3 means that the colors are in ASCII
    image_file << "P3\n";
    // Specifies image width and height
    const double kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 400;
    const int kImageHeight = static_cast<int>(kImageWidth / kAspectRatio);
    image_file << kImageWidth << " " << kImageHeight << "\n";
    // Camera Specifications
    const double kViewportHeight = 2.0;
    const double kViewportWidth = kAspectRatio * kViewportHeight;
    const double kFocalLength = 1.0;

    const point3 kOrigin = point3(); // point3 defaults to be the zero vector
    const vec3 kHorizontalDirection = vec3(kViewportWidth, 0, 0);
    const vec3 kVerticalDirection = vec3(0, kViewportHeight, 0);
    const point3 kLowerLeftCorner = kOrigin - (kHorizontalDirection / 2) - (kVerticalDirection / 2)
        - vec3(0, 0, kFocalLength);

    // Specifies the max color for the RGB triplets
    const int kMaxColor = 255;
    image_file << kMaxColor << "\n";

    // Write RGB triplets to the file
    // pixels are written out in rows from top to bottom that go left to right
    for (int i = kImageHeight - 1; i >= 0; --i) {
      std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
      for (int j = 0; j < kImageWidth; ++j) {
        const double kHorizontalFactor = double(j) / (kImageWidth - 1);
        const double kVerticalFactor = double(i) / (kImageHeight - 1);
        const vec3 kRayDirection = kLowerLeftCorner + (kHorizontalDirection * kHorizontalFactor) 
            + (kVerticalDirection * kVerticalFactor) - kOrigin;
        const ray kRay = ray(kOrigin, kRayDirection);
        // add pixel to the ppm file
        writeColor(image_file, rayColor(kRay));
      }
    }
  }
  image_file.close();
  std::cerr << "\nDone.\n";
}

void outputBasicImageToFile(std::string file_name) {
  std::ofstream image_file = std::ofstream(file_name, std::ios::ate);
  if (image_file.is_open()){
    // P3 means that the colors are in ASCII
    image_file << "P3\n";
    // Specifies that there are 256 columns and 256 rows
    const int kImageSize = 256;
    image_file << kImageSize << " " << kImageSize << "\n";
    // Specifies the max color for the RGB triplets
    const int kMaxColor = 255;
    image_file << kMaxColor << "\n";

    // Write RGB triplets to the file
    const double kBlue = 0.25;
    // pixels are written out in rows from top to bottom that go left to right
    // green depends on i and goes from fully on to fully off
    for (int i = kImageSize - 1; i >= 0; --i) {
      std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
      // red depends on j and goes from fully off to fully on
      for (int j = 0; j < kImageSize; ++j) {
        // RGB components range from [0,1] by convention
        const double kRed = double(j) / (kImageSize - 1);
        const double kGreen = double(i) / (kImageSize - 1);

        const color kPixelColor = color(kRed, kGreen, kBlue);
        // add pixel to the ppm file
        writeColor(image_file, kPixelColor);
      }
    }
  }
  image_file.close();
  std::cerr << "\nDone.\n";
}

int main() {
  outputBasicImageToFile("results/basicImage.ppm");
  basicSphere("results/visualizingSurfaceNormals.ppm");
  return 0;
}
