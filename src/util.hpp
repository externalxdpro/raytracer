#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>
#include <limits>
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

#endif // UTIL_H_
