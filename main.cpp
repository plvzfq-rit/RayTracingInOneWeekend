#include <cmath>
#include <iostream>

#include "color.h"
#include "Ray.h"
#include "Vector3D.h"

double calculateSphereHitTime(const Point3D& center, double radius, const Ray& r) {
    Vector3D oc = center - r.origin();
    auto a = r.direction().lengthSquared();
    auto h = dot(r.direction(), oc);
    auto c = oc.lengthSquared() - radius * radius;
    auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}

Color rayColor(const Ray& ray) {
    auto sphereContactTime = calculateSphereHitTime(Point3D(0,0,-1), 0.5, ray);
    if (sphereContactTime > 0.0) {
        Vector3D normalVector = normalize(ray.at(sphereContactTime) - Vector3D(0,0,-1));
        return 0.5 * Color(normalVector.x() + 1, normalVector.y() + 1, normalVector.z() + 1);
    }

    Vector3D unitDirection = normalize(ray.direction());
    auto BLUE_WEIGHT = 0.5 * (unitDirection.y() + 1.0);
    auto WHITE_WEIGHT = 1 - BLUE_WEIGHT;
    auto WHITE = Color(1.0, 1.0, 1.0);
    auto BLUE = Color(0.5, 0.7, 1.0);
    return WHITE_WEIGHT * WHITE + BLUE_WEIGHT * BLUE;
}

int main() {
    auto ASPECT_RATIO = 16.0 / 9.0;
    int IMAGE_WIDTH = 400;

    int IMAGE_HEIGHT = int(IMAGE_WIDTH / ASPECT_RATIO);
    IMAGE_HEIGHT = (IMAGE_HEIGHT < 1) ? 1 : IMAGE_HEIGHT;

    auto FOCAL_LENGTH = 1.0;
    auto VIEWPORT_HEIGHT = 2.0;
    auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH) / IMAGE_HEIGHT);
    auto CAMERA_CENTER = Point3D(0,0,0);

    auto VIEWPORT_HORIZONTAL = Vector3D(VIEWPORT_WIDTH, 0, 0);
    auto VIEWPORT_VERTICAL = Vector3D(0, -VIEWPORT_HEIGHT, 0);

    auto HORIZONTAL_PIXEL_CHANGE = VIEWPORT_HORIZONTAL / IMAGE_WIDTH;
    auto VERTICAL_PIXEL_CHANGE = VIEWPORT_VERTICAL / IMAGE_HEIGHT;

    auto VIEWPORT_UPPER_LEFT = CAMERA_CENTER -
        Vector3D(0,0,FOCAL_LENGTH) - VIEWPORT_HORIZONTAL / 2 - VIEWPORT_VERTICAL / 2;

    auto FIRST_PIXEL_LOCATION = VIEWPORT_UPPER_LEFT + 0.5 * (HORIZONTAL_PIXEL_CHANGE + VERTICAL_PIXEL_CHANGE);


    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for (int currentRow = 0; currentRow < IMAGE_HEIGHT; currentRow++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - currentRow) << " " << std::flush;
        for (int currentColumn = 0; currentColumn < IMAGE_WIDTH; currentColumn++) {
            auto pixelCenter = FIRST_PIXEL_LOCATION + (currentColumn * HORIZONTAL_PIXEL_CHANGE) + (currentRow * VERTICAL_PIXEL_CHANGE);
            auto rayDirection = pixelCenter - CAMERA_CENTER;
            Ray r(CAMERA_CENTER, rayDirection);

            Color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                             \n";
    return 0;
}