#include <cmath>
#include <iostream>

#include "Camera.h"
#include "color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "math_stuff.h"
#include "Sphere.h"
#include "Ray.h"
#include "Vector3D.h"

int main() {
    HittableList world;

    auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<Dielectric>(1.50);
    auto materialBubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3D(0.0,-100.5,-1.0), 100.0, materialGround));
    world.add(std::make_shared<Sphere>(Point3D(0.0,0.0,-1.2), 0.5, materialCenter));
    world.add(std::make_shared<Sphere>(Point3D(-1.0,0.0,-1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(Point3D(-1.0,0.0,-1.0), 0.4, materialBubble));
    world.add(std::make_shared<Sphere>(Point3D(1.0,0.0,-1.0), 0.5, materialRight));

    Camera camera;
    camera.ASPECT_RATIO = 16.0 / 9.0;
    camera.IMAGE_WIDTH = 1200;
    camera.SAMPLES_PER_PIXEL = 500;
    camera.MAX_DEPTH = 50;
    camera.INTENSITY = 0.5;
    camera.VERTICAL_FIELD_OF_VIEW = 20;
    camera.LOOK_FROM = Point3D(13, 2, 3);
    camera.LOOK_AT = Point3D(0, 0, 0);
    camera.UP_VECTOR = Vector3D(0, 1, 0);
    camera.DEFOCUS_ANGLE = 0.6;
    camera.FOCUS_DISTANCE = 10.0;
    camera.render(world);

    return 0;
}