#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>
#include <format>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

const double inf = std::numeric_limits<double>::infinity();
const double pi  = M_PI;

inline double degToRad(double deg) { return deg * pi / 180.0; }

inline double randDouble() {
    static std::uniform_real_distribution<double> dist(0, 1);
    static std::mt19937                           gen;
    return dist(gen);
}

inline double randDouble(double min, double max) {
    return min + (max - min) * randDouble();
}

#include "colour.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif // UTIL_H_
