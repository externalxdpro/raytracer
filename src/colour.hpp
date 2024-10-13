#ifndef COLOUR_H_
#define COLOUR_H_

#include "vec3.hpp"

#include <format>
#include <iostream>

using Colour = Vec3;

inline void writeColour(std::ostream &out, const Colour &pixelColour) {
    int r = 255.999 * pixelColour.x;
    int g = 255.999 * pixelColour.y;
    int b = 255.999 * pixelColour.z;

    out << std::format("{} {} {}\n", r, g, b);
}

#endif // COLOUR_H_
