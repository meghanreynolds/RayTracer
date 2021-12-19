#include <iostream>
#include <fstream>
#include <string>

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
    const int kIntBlue = static_cast<int>(255.999 * kBlue);
    // pixels are written out in rows from top to bottom that go left to right
    // green depends on i and goes from fully on to fully off
    for (int i = kImageSize - 1; i >= 0; --i) {
      std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
      // red depends on j and goes from fully off to fully on
      for (int j = 0; j < kImageSize; ++j) {
        // RGB components range from [0,1] by convention
        const double kRed = double(j) / (kImageSize - 1);
        const double kGreen = double(i) / (kImageSize - 1);

        const int kIntRed = static_cast<int>(255.999 * kRed);
        const int kIntGreen = static_cast<int>(255.999 * kGreen);
        image_file << kIntRed << ' ' << kIntGreen << ' ' << kIntBlue << '\n';
      }
    }
  }
  image_file.close();
  std::cerr << "\nDone.\n";
}

int main() {
  outputBasicImageToFile("results/basicImage.ppm");
  return 0;
}
