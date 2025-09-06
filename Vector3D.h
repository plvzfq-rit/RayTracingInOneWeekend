//
// Created by James Christian on 06/09/2025.
//

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <iostream>

#include "math_stuff.h"

class Vector3D {
public:
    double v[3];

    Vector3D(): v{0,0,0} {}
    Vector3D(double v1, double v2, double v3): v{v1, v2, v3} {}

    double x() const {
        return v[0];
    }

    double y() const {
        return v[1];
    }

    double z() const {
        return v[2];
    }

    Vector3D operator-() const {
        return Vector3D(-v[0], -v[1], -v[2]);
    }

    double operator[](int i) const {
        return v[i];
    }

    double& operator[](int i) {
        return v[i];
    }

    Vector3D& operator+=(const Vector3D& v) {
        this->v[0] += v[0];
        this->v[1] += v[1];
        this->v[2] += v[2];
        return *this;
    }

    Vector3D& operator*=(double t) {
        this->v[0] *= t;
        this->v[1] *= t;
        this->v[2] *= t;
        return *this;
    }

    Vector3D& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    }

    bool nearZero() const {
        auto TOLERANCE = 1e-8;
        return (std::fabs(v[0]) < TOLERANCE) && (std::fabs(v[1]) < TOLERANCE) && (std::fabs(v[2]) < TOLERANCE);
    }

    static Vector3D random() {
        return Vector3D(randomDouble(), randomDouble(), randomDouble());
    }

    static Vector3D random(double min, double max) {
        return Vector3D(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

using Point3D = Vector3D;

inline std::ostream& operator<<(std::ostream& out, const Vector3D& v) {
    return out << v.v[0] << ' ' << v.v[1] << ' ' << v.v[2];
}

inline Vector3D operator+(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.v[0] + v.v[0], u.v[1] + v.v[1], u.v[2] + v.v[2]);
}

inline Vector3D operator-(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.v[0] - v.v[0], u.v[1] - v.v[1], u.v[2] - v.v[2]);
}

inline Vector3D operator*(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.v[0] * v.v[0], u.v[1] * v.v[1], u.v[2] * v.v[2]);
}

inline Vector3D operator*(double t, const Vector3D& v) {
    return Vector3D(v.v[0] * t, v.v[1] * t, v.v[2] * t);
}

inline Vector3D operator*(const Vector3D& v, double t) {
    return t * v;
}

inline Vector3D operator/(const Vector3D& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3D& u, const Vector3D& v) {
    return u.v[0] * v.v[0] + u.v[1] * v.v[1] + u.v[2] * v.v[2];
}

inline Vector3D cross(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.v[1] * v.v[2] - u.v[2] * v.v[1],
        u.v[2] * v.v[0] - u.v[0] * v.v[2],
        u.v[0] * v.v[1] - u.v[1] * v.v[0]);
}

inline Vector3D normalize(const Vector3D& v) {
    return v / v.length();
}

inline Vector3D randomInUnitDisk() {
    while (true) {
        auto point = Vector3D(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (point.lengthSquared() < 1) {
            return point;
        }
    }
}

inline Vector3D randomUnitVector() {
    while (true) {
        auto vector = Vector3D::random(-1, 1);
        auto lengthSquared = vector.lengthSquared();
        if (1e-160 < lengthSquared && lengthSquared <= 1) {
            return vector / std::sqrt(lengthSquared);
        }
    }
}

inline Vector3D randomOnHemisphere(const Vector3D& normalVector) {
    Vector3D onUnitSphere = randomUnitVector();
    if (dot(onUnitSphere, normalVector) > 0) {
        return onUnitSphere;
    } else {
        return -onUnitSphere;
    }
}

inline Vector3D reflect(const Vector3D& v, const Vector3D& n) {
    return v - 2 * dot(v,n) * n;
}

inline Vector3D refract(const Vector3D& uv, const Vector3D& n, double refractiveQuotient) {
    auto cosineOfRefractionAngle = std::fmin(dot(-uv, n), 1.0);
    Vector3D rayOutPerpendicular = refractiveQuotient * (uv + cosineOfRefractionAngle * n);
    Vector3D rayOutParallel = -std::sqrt(std::fabs(1.0 - rayOutPerpendicular.lengthSquared())) * n;
    return rayOutPerpendicular + rayOutParallel;
}

#endif //VECTOR3D_H
