#ifndef COLOUR_H_
#define COLOUR_H_

#include "ray.hpp"
#include "vec3.hpp"

#include <format>
#include <iostream>

using Colour = Vec3;

inline Colour rayColour(Ray &r) {
    Vec3   unitDir = r.dir.unitVector();
    double a       = (unitDir.y + 1) / 2;
    return Colour(1, 1, 1) * (1.0 - a) + Colour(0.5, 0.7, 1.0) * a;
}

inline void writeColour(std::ostream &out, const Colour &pixelColour) {
    int r = 255.999 * pixelColour.x;
    int g = 255.999 * pixelColour.y;
    int b = 255.999 * pixelColour.z;

    out << std::format("{} {} {}\n", r, g, b);
}

#endif // COLOUR_H_
