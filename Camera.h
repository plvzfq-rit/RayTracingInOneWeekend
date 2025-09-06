//
// Created by James Christian on 06/09/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "Hittable.h"
#include "Material.h"

class Camera {
public:
    double ASPECT_RATIO = 1.0;
    int IMAGE_WIDTH = 100;
    int SAMPLES_PER_PIXEL = 10;
    int MAX_DEPTH = 10;
    double INTENSITY = 1.0;

    double VERTICAL_FIELD_OF_VIEW = 90;
    Point3D LOOK_FROM = Point3D(0,0,0);
    Point3D LOOK_AT = Point3D(0,0,-1);
    Vector3D UP_VECTOR = Vector3D(0,1,0);

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
    Vector3D HORIZONTAL_BASIS_VECTOR;
    Vector3D VERTICAL_BASIS_VECTOR;
    Vector3D DEPTH_BASIS_VECTOR;

    void initialize() {
        IMAGE_HEIGHT = int(IMAGE_WIDTH / ASPECT_RATIO);
        IMAGE_HEIGHT = (IMAGE_HEIGHT < 1) ? 1 : IMAGE_HEIGHT;
        PIXEL_SAMPLES_SCALE = 1.0 / SAMPLES_PER_PIXEL;

        CAMERA_CENTER = LOOK_FROM;

        auto FOCAL_LENGTH = (LOOK_FROM - LOOK_AT).length();
        auto VFOV_RADIAN = degreesToRadians(VERTICAL_FIELD_OF_VIEW);
        auto h = std::tan(VFOV_RADIAN / 2);

        auto VIEWPORT_HEIGHT = 2.0 * h * FOCAL_LENGTH;
        auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH) / IMAGE_HEIGHT);

        DEPTH_BASIS_VECTOR = normalize(LOOK_FROM - LOOK_AT);
        HORIZONTAL_BASIS_VECTOR = normalize(cross(UP_VECTOR, DEPTH_BASIS_VECTOR));
        VERTICAL_BASIS_VECTOR = cross(DEPTH_BASIS_VECTOR, HORIZONTAL_BASIS_VECTOR);

        auto VIEWPORT_HORIZONTAL = VIEWPORT_WIDTH * HORIZONTAL_BASIS_VECTOR;
        auto VIEWPORT_VERTICAL = VIEWPORT_HEIGHT * -VERTICAL_BASIS_VECTOR;

        HORIZONTAL_PIXEL_CHANGE = VIEWPORT_HORIZONTAL / IMAGE_WIDTH;
        VERTICAL_PIXEL_CHANGE = VIEWPORT_VERTICAL / IMAGE_HEIGHT;

        auto VIEWPORT_UPPER_LEFT = CAMERA_CENTER -
            (FOCAL_LENGTH * DEPTH_BASIS_VECTOR) - VIEWPORT_HORIZONTAL / 2 - VIEWPORT_VERTICAL / 2;

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
        if (depth <= 0) {
            return Color(0,0,0);
        }

        HitRecord record;

        if (world.hitInTimeRange(ray, Interval(0.001, INFTY), record)) {
            Ray scattered;
            Color attenuation;
            if (record.material->scatter(ray, record, attenuation, scattered)) {
                return attenuation * rayColor(scattered, depth - 1, world);
            }
            return Color(0,0,0);
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
