//
// Created by James Christian on 06/09/2025.
//

#include <cmath>

#include "Vector3D.h"

inline Vector3D::Vector3D(): v{0,0,0} {}

inline Vector3D::Vector3D(double v1, double v2, double v3): v{v1, v2, v3} {}

inline double Vector3D::x() const {
    return v[0];
}

inline double Vector3D::y() const {
    return v[1];
}

inline double Vector3D::z() const {
    return v[2];
}

inline Vector3D Vector3D::operator-() const {
    return Vector3D(-v[0], -v[1], -v[2]);
}

inline double Vector3D::operator[](int i) const {
    return v[i];
}

inline double & Vector3D::operator[](int i) {
    return v[i];
}

inline Vector3D & Vector3D::operator+=(const Vector3D &v) {
    this->v[0] += v[0];
    this->v[1] += v[1];
    this->v[2] += v[2];
    return *this;
}

inline Vector3D & Vector3D::operator*=(double t) {
    this->v[0] *= t;
    this->v[1] *= t;
    this->v[2] *= t;
    return *this;
}

inline Vector3D & Vector3D::operator/=(double t) {
    return *this *= 1/t;
}

inline double Vector3D::length() const {
    return std::sqrt(lengthSquared());
}

inline double Vector3D::lengthSquared() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}