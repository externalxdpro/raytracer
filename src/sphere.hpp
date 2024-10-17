#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.hpp"

#include <memory>

class Sphere : public Hittable {
  public:
    Vec3                      center;
    double                    radius;
    std::shared_ptr<Material> mat;

    Sphere(const Vec3 &center, double radius, std::shared_ptr<Material> mat)
        : center(center), radius(std::fmax(0, radius)), mat(mat) {}

    bool hit(const Ray &r, Interval t, HitRecord &rec) const override {
        Vec3 oc = center - r.origin;

        // Do quadratic formula to calculate t in
        // t^2(dir . dir) - 2t(dir) . oc + (oc . oc - radius^2)
        // to check if ray hit sphere
        double a = r.dir.lengthSquared();
        double h = r.dir.dot(oc);
        double c = oc.lengthSquared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        double root = (h - sqrtd) / a;
        if (!t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.setFaceNormal(r, (rec.p - center) / radius);
        rec.mat = mat;

        return true;
    }
};

#endif // SPHERE_H_
