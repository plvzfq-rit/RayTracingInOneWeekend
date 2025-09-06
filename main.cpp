#include <iostream>

int main() {
    int imageWidth = 256;
    int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            int ir = int(r * 255.999);
            int ig = int(g * 255.999);
            int ib = int(b * 255.999);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}