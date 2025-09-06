//
// Created by James Christian on 06/09/2025.
//

#ifndef MATH_STUFF_H
#define MATH_STUFF_H
#include <limits>
#include <random>

const double INFTY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

#endif //MATH_STUFF_H
