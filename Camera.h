//
// Created by James Christian on 06/09/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "Hittable.h"

class Camera {
public:
    double ASPECT_RATIO = 1.0;
    int IMAGE_WIDTH = 100;
    int SAMPLES_PER_PIXEL = 10;
    int MAX_DEPTH = 10;
    double INTENSITY = 1.0;

    void render(const Hittable& world) {
        initialize();

        std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

        for (int currentRow = 0; currentRow < IMAGE_HEIGHT; currentRow++) {
            std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - currentRow) << " " << std::flush;
            for (int currentColumn = 0; currentColumn < IMAGE_WIDTH; currentColumn++) {
                Color pixelColor(0,0,0);
                for (int sample = 0; sample < SAMPLES_PER_PIXEL; sample++) {
                    Ray ray = getRay(currentColumn, currentRow);
                    pixelColor += rayColor(ray, MAX_DEPTH, world);
                }
                writeColor(std::cout, PIXEL_SAMPLES_SCALE * pixelColor);
            }
        }

        std::clog << "\rDone.                             \n";
    }

private:
    int IMAGE_HEIGHT;
    double PIXEL_SAMPLES_SCALE;
    Point3D CAMERA_CENTER;
    Point3D FIRST_PIXEL_LOCATION;
    Vector3D HORIZONTAL_PIXEL_CHANGE;
    Vector3D VERTICAL_PIXEL_CHANGE;

    void initialize() {
        IMAGE_HEIGHT = int(IMAGE_WIDTH / ASPECT_RATIO);
        IMAGE_HEIGHT = (IMAGE_HEIGHT < 1) ? 1 : IMAGE_HEIGHT;
        PIXEL_SAMPLES_SCALE = 1.0 / SAMPLES_PER_PIXEL;
        auto FOCAL_LENGTH = 1.0;
        auto VIEWPORT_HEIGHT = 2.0;
        auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH) / IMAGE_HEIGHT);
        CAMERA_CENTER = Point3D(0,0,0);

        auto VIEWPORT_HORIZONTAL = Vector3D(VIEWPORT_WIDTH, 0, 0);
        auto VIEWPORT_VERTICAL = Vector3D(0, -VIEWPORT_HEIGHT, 0);

        HORIZONTAL_PIXEL_CHANGE = VIEWPORT_HORIZONTAL / IMAGE_WIDTH;
        VERTICAL_PIXEL_CHANGE = VIEWPORT_VERTICAL / IMAGE_HEIGHT;

        auto VIEWPORT_UPPER_LEFT = CAMERA_CENTER -
            Vector3D(0,0,FOCAL_LENGTH) - VIEWPORT_HORIZONTAL / 2 - VIEWPORT_VERTICAL / 2;

        FIRST_PIXEL_LOCATION = VIEWPORT_UPPER_LEFT + 0.5 * (HORIZONTAL_PIXEL_CHANGE + VERTICAL_PIXEL_CHANGE);
    }

    Ray getRay(int i, int j) {
        auto offset = sampleSquare();
        auto pixelSample = FIRST_PIXEL_LOCATION +
            ((i + offset.x()) * HORIZONTAL_PIXEL_CHANGE) +
                ((j + offset.y()) * VERTICAL_PIXEL_CHANGE);

        auto rayOrigin = CAMERA_CENTER;
        auto rayDirection = pixelSample - rayOrigin;
        return Ray(rayOrigin, rayDirection);
    }

    Vector3D sampleSquare() const {
        return Vector3D(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }

    Color rayColor(const Ray& ray, int depth, const Hittable& world) const {
        HitRecord record;
        if (depth <= 0) {
            return Color(0,0,0);
        }

        if (world.hitInTimeRange(ray, Interval(0.001, INFTY), record)) {
            Vector3D direction = record.normalVector + randomUnitVector();
            return INTENSITY * rayColor(Ray(record.point, direction), depth - 1, world);
        }

        Vector3D unitDirection = normalize(ray.direction());
        auto BLUE_WEIGHT = 0.5 * (unitDirection.y() + 1.0);
        auto WHITE_WEIGHT = 1 - BLUE_WEIGHT;
        auto WHITE = Color(1.0, 1.0, 1.0);
        auto BLUE = Color(0.5, 0.7, 1.0);
        return WHITE_WEIGHT * WHITE + BLUE_WEIGHT * BLUE;
    }
};
#endif //CAMERA_H
