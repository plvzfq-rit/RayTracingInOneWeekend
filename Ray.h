//
// Created by James Christian on 06/09/2025.
//

#ifndef RAY_H
#define RAY_H
#include "Vector3D.h"

class Ray {
    public:
    Ray() {}
    Ray(const Point3D& originArg, const Vector3D& directionArg) : originAttribute(originArg), directionAttribute(directionArg) {}

    const Point3D& origin() const {
        return originAttribute;
    }

    const Vector3D& direction() const {
        return  directionAttribute;
    }

    Point3D at(double t) const {
        return originAttribute + t * directionAttribute;
    }

private:
    Point3D originAttribute;
    Vector3D directionAttribute;
};
#endif //RAY_H
