#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Hittable {
  public:
    class HitRecord {
      public:
        Vec3   p;
        Vec3   normal;
        double t;
        bool   frontFace;

        void setFaceNormal(const Ray &r, const Vec3 &outwardNormal) {
            // NOTE: outwardNormal is expected to have unit length
            frontFace = r.dir.dot(outwardNormal) < 0;
            normal    = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    virtual ~Hittable() = default;

    virtual bool hit(const Ray &r, Interval t, HitRecord &rec) const = 0;
};

#endif // HITTABLE_H_
