#ifndef COLOUR_H_
#define COLOUR_H_

#include "interval.hpp"
#include "vec3.hpp"

using Colour = Vec3;

inline void writeColour(std::ostream &out, const Colour &pixelColour) {
    static const Interval intensity(0, 0.999);

    int rbyte = 256 * intensity.clamp(pixelColour.x);
    int gbyte = 256 * intensity.clamp(pixelColour.y);
    int bbyte = 256 * intensity.clamp(pixelColour.z);

    out << std::format("{} {} {}\n", rbyte, gbyte, bbyte);
}

#endif // COLOUR_H_
