//
// Created by James Christian on 06/09/2025.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord {
public:
    Point3D point;
    Vector3D normalVector;
    double time;
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hitInTimeRange(const Ray& ray, double minTime, double maxTime, HitRecord& record) const = 0;
};

#endif //HITTABLE_H
