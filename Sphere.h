//
// Created by James Christian on 06/09/2025.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vector3D.h"

class Sphere: public Hittable {
public:
    Sphere(const Point3D& center, double radius): center(center), radius(std::fmax(0, radius)) {}
    bool hitInTimeRange(const Ray& ray, double minTime, double maxTime, HitRecord& record) const override {
        Vector3D oc = center - r.origin();
        auto a = r.direction().lengthSquared();
        auto h = dot(r.direction(), oc);
        auto c = oc.lengthSquared() - radius * radius;
        auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        auto sqrtDiscriminant = std::sqrt(discriminant);

        auto root = (h - sqrtDiscriminant) / a;
        if (root <= minTime || maxTime <= root) {
            root = (h + sqrtDiscriminant) / a;
            if (root <= minTime || maxTime <= root) {
                return false;
            }
        }

        record.time = root;
        record.point = ray.at(record.time);
        Vector3D outwardNormal = (record.point - center) / radius;
        record.setFaceNormal(ray, outwardNormal);

        return true;
    }

private:
    Point3D center;
    double radius;
};

#endif //SPHERE_H
