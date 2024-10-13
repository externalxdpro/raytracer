#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "ray.hpp"

class Hittable {
  public:
    struct HitRecord {
        Vec3   p;
        Vec3   normal;
        double t;
    };

    virtual ~Hittable() = default;

    virtual bool hit(const Ray &r, double tMin, double tMax,
                     HitRecord &rec) const = 0;
};

#endif // HITTABLE_H_
