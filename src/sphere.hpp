#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
  public:
    Vec3   center;
    double radius;

    Sphere(const Vec3 &center, double radius)
        : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const Ray &r, double tMin, double tMax,
             HitRecord &rec) const override {
        Vec3 oc = center - r.origin;

        // Do quadratic formula to calculate t in
        // t^2(dir . dir) - 2t(dir) . oc + (oc . oc - radius^2)
        // to check if ray hit sphere
        double a = r.dir.length_squared();
        double h = r.dir.dot(oc);
        double c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        double root = (h - sqrtd) / a;
        if (root <= tMin || tMax <= root) {
            root = (h + sqrtd) / a;
            if (root <= tMin || tMax <= root) {
                return false;
            }
        }

        rec.t      = root;
        rec.p      = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }
};

#endif // SPHERE_H_
