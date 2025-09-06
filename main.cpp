#include <iostream>

#include "color.h"
#include "Vector3D.h"

int main() {
    int imageWidth = 256;
    int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;

            auto pixelColor = Color(double(i)/(imageWidth-1), double(j)/(imageHeight-1), 0);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                             \n";
    return 0;
}