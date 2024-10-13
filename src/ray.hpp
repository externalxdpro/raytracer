#ifndef RAY_H_
#define RAY_H_

#include "vec3.hpp"

class Ray {
  public:
    Vec3 origin;
    Vec3 dir;

    Ray() {}
    Ray(const Vec3 &origin, const Vec3 &dir) : origin(origin), dir(dir) {}

    Vec3 at(double t) const { return origin + dir * t; }
};

#endif // RAY_H_
