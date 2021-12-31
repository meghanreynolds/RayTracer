#include <iostream>
#include <fstream>
#include <string>

#include "camera.h"
#include "camera.cpp"
#include "constants_and_utilities.h"
#include "Hittable.h"
#include "hittable_list.h"
#include "hittable_list.cpp"
#include "ray.h"
#include "ray.cpp"
#include "sphere.h"
#include "sphere.cpp"
#include "vec3.h"
#include "vec3.cpp"



color rayColor(const ray& kRay, const Hittable& objects) {
  // find closest hit object (if an object was hit)
  HitRecord hit_record = HitRecord();
  const bool kWasHit = objects.wasHit(kRay, 0, infinity, hit_record);

  // ensure the ray hits an object before visualizing surface normals
  if (kWasHit) {
    const vec3 kUnitSurfaceNormal = hit_record.surface_normal_;
    // adding 1 to each component ensures each component >= 0 and 
    // multiplting by 0.5 ensures each component <= 1
    return (kUnitSurfaceNormal + color(1, 1, 1)) * 0.5;
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

void normalSphereWithGround(std::string file_name) {
  std::ofstream image_file = std::ofstream(file_name, std::ios::ate);
  if (image_file.is_open()){
    // P3 means that the colors are in ASCII
    image_file << "P3\n";
    // Specifies image width and height
    const double kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 400;
    const int kImageHeight = static_cast<int>(kImageWidth / kAspectRatio);
    image_file << kImageWidth << " " << kImageHeight << "\n";
    // Create World with 2 spheres (first is colorful sphere and second represents green ground)
    hittable_list world = hittable_list(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    // add a camera to the scene
    const camera kCameraOne = camera();

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
        const ray kRay = kCameraOne.getRay(kHorizontalFactor, kVerticalFactor);
        // add pixel to the ppm file
        const color kPixelColor = rayColor(kRay, world);
        writeColor(image_file, kPixelColor);
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
  normalSphereWithGround("results/normalSphereWithGround.ppm");
  return 0;
}
