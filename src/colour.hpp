#ifndef COLOUR_H_
#define COLOUR_H_

#include "interval.hpp"
#include "vec3.hpp"

#include <cmath>

using Colour = Vec3;

inline double linearToGamma(double linearComponent) {
    if (linearComponent > 0) {
        return std::sqrt(linearComponent);
    }
    return 0;
}

inline void writeColour(std::ostream &out, const Colour &pixelColour) {
    static const Interval intensity(0, 0.999);

    int r = 256 * intensity.clamp(linearToGamma(pixelColour.x));
    int g = 256 * intensity.clamp(linearToGamma(pixelColour.y));
    int b = 256 * intensity.clamp(linearToGamma(pixelColour.z));

    out << std::format("{} {} {}\n", r, g, b);
}

#endif // COLOUR_H_
