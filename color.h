//
// Created by James Christian on 06/09/2025.
//

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "Vector3D.h"

using Color = Vector3D;

inline void writeColor(std::ostream& os, const Color& color) {
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();

    int rByte = int(255.999 * r);
    int gByte = int(255.999 * g);
    int bByte = int(255.999 * b);

    std::cout << rByte << " " << gByte << " " << bByte << "\n";
}

#endif //COLOR_H
