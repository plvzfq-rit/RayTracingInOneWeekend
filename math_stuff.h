//
// Created by James Christian on 06/09/2025.
//

#ifndef MATH_STUFF_H
#define MATH_STUFF_H
#include <limits>

const double INFTY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

#endif //MATH_STUFF_H
