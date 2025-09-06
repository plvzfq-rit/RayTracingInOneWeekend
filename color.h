//
// Created by James Christian on 06/09/2025.
//

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "Interval.h"
#include "Vector3D.h"

using Color = Vector3D;

inline double linearToGamma(double linearComponent) {
    if (linearComponent > 0.0) {
        return std::sqrt(linearComponent);
    }
    return 0.0;
}

inline void writeColor(std::ostream& os, const Color& color) {
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const Interval intensity(0.0, 0.999);
    int rByte = int(256 * intensity.clamp(r));
    int gByte = int(256 * intensity.clamp(g));
    int bByte = int(256 * intensity.clamp(b));

    std::cout << rByte << " " << gByte << " " << bByte << "\n";
}

#endif //COLOR_H
