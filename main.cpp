#include <iostream>
#include <fstream>
#include <string>

#include "camera.h"
#include "camera.cpp"
#include "constants_and_utilities.h"
#include "constants_and_utilities.cpp"
#include "Hittable.h"
#include "hittable_list.h"
#include "hittable_list.cpp"
#include "ray.h"
#include "ray.cpp"
#include "sphere.h"
#include "sphere.cpp"
#include "vec3.h"
#include "vec3.cpp"



color rayColor(const ray& kRay, const Hittable& objects, size_t depth) {
  // find closest hit object (if an object was hit)
  HitRecord hit_record = HitRecord();
  // ignore hits that are extremely close to 0 to fix shadow acne 
  const double kMinT = 0.001;
  const bool kWasHit = objects.wasHit(kRay, kMinT, infinity, hit_record);

  // ensure the ray hits an object before adding diffuse material
  if (kWasHit) {
    const point3 kRandomPointInTangentUnitSphere = hit_record.point_of_intersection_ 
        + hit_record.surface_normal_ + randomPointInUnitSphere();
    const ray kRandomRay = ray(hit_record.point_of_intersection_, kRandomPointInTangentUnitSphere 
        - hit_record.point_of_intersection_);
        
    if (depth > 0) {
      // multiplting by 0.5 ensures each component <= 1
      return rayColor(kRandomRay, objects, depth - 1) * 0.5;
    } else {
      // after ray bounce limit is exceeded, return no light
      return color(0, 0, 0);
    }
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

void diffuseSphere(std::string file_name) {
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
    // Specifies number of color samples to take per pixel
    const int kNumSamplesPerPixel = 100;

    // Write RGB triplets to the file
    // pixels are written out in rows from top to bottom that go left to right
    for (int i = kImageHeight - 1; i >= 0; --i) {
      std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
      for (int j = 0; j < kImageWidth; ++j) {
        // antialiasing sampling
        color pixel_color = color(); // defaults to zero vector
        for (int k = 0; k < kNumSamplesPerPixel; ++k) {
          const double kHorizontalFactor = (j + randomDouble()) / (kImageWidth - 1);
          const double kVerticalFactor = (i + randomDouble()) / (kImageHeight - 1);
          const ray kRay = kCameraOne.getRay(kHorizontalFactor, kVerticalFactor);
          const size_t kMaxNumRayBounces = 50;
          pixel_color += rayColor(kRay, world, kMaxNumRayBounces);
        }
        // add pixel to the ppm file 
        writeColor(image_file, pixel_color, kNumSamplesPerPixel);
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
        writeColor(image_file, kPixelColor, 1);
      }
    }
  }
  image_file.close();
  std::cerr << "\nDone.\n";
}

int main() {
  outputBasicImageToFile("results/basicImage.ppm");
  diffuseSphere("results/diffuseSphere.ppm");
  return 0;
}
