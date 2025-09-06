//
// Created by James Christian on 06/09/2025.
//

#ifndef INTERVAL_H
#define INTERVAL_H

#include "math_stuff.h"

class Interval {
public:
    double min;
    double max;

    Interval() : min(+INFTY), max(-INFTY) {}
    Interval(double min, double max): min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains (double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(INFTY, -INFTY);
const Interval Interval::universe = Interval(-INFTY, INFTY);

#endif //INTERVAL_H
