#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>
#include <format>
#include <iostream>
#include <limits>
#include <memory>

const double inf = std::numeric_limits<double>::infinity();
const double pi  = M_PI;

inline double degToRad(double deg) { return deg * pi / 180.0; }

#include "colour.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif // UTIL_H_
