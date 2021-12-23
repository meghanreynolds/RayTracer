#include <iostream>
#include <fstream>
#include <string>

#include "ray.h"
#include "ray.cpp"
#include "vec3.h"
#include "vec3.cpp"

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
  basicSphere("results/basicSphere.ppm");
  return 0;
}
