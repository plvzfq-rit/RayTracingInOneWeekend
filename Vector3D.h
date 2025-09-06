//
// Created by James Christian on 06/09/2025.
//

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3D {
public:
    double v[3];

    Vector3D();
    Vector3D(double v1, double v2, double v3);

    double x() const;
    double y() const;
    double z() const;

    Vector3D operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vector3D& operator+=(const Vector3D& v);
    Vector3D& operator*=(double t);
    Vector3D& operator/=(double t);

    double length() const;
    double lengthSquared() const;
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



#endif //VECTOR3D_H
