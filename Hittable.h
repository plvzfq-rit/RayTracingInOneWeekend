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
    bool isFrontFace;

    void setFaceNormal(const Ray& ray, const Vector3D& outwardNormal) {
        if (outwardNormal.length() != 1.0) {
            throw std::invalid_argument("The outward normal vector must be normalized. Was: " + std::to_string(outwardNormal.length()));
        }
        isFrontFace = dot(ray.direction(), outwardNormal) < 0;
        normalVector = isFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hitInTimeRange(const Ray& ray, double minTime, double maxTime, HitRecord& record) const = 0;
};

#endif //HITTABLE_H
