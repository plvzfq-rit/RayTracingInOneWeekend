#include <cmath>
#include <iostream>

#include "Camera.h"
#include "color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "math_stuff.h"
#include "Sphere.h"
#include "Ray.h"
#include "Vector3D.h"

int main() {
    HittableList world;

    world.add(std::make_shared<Sphere>(Point3D(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Point3D(0,-100.5,-1), 100));

    Camera camera;
    camera.ASPECT_RATIO = 16.0 / 9.0;
    camera.IMAGE_WIDTH = 400;

    camera.render(world);

    return 0;
}