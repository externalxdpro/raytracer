#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "colour.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &rIn, const Hittable::HitRecord &rec,
                         Colour &attenuation, Ray &scattered) const {
        return false;
    }
};

class Lambertian : public Material {
  public:
    Lambertian(const Colour &albedo) : albedo(albedo) {}

    bool scatter(const Ray &rIn, const Hittable::HitRecord &rec,
                 Colour &attenuation, Ray &scattered) const override {
        Vec3 scatterDir = rec.normal + Vec3::randUnitVector();

        if (scatterDir.nearZero()) {
            scatterDir = rec.normal;
        }

        scattered   = Ray(rec.p, scatterDir);
        attenuation = albedo;
        return true;
    }

  private:
    Colour albedo;
};

class Metal : public Material {
  public:
    Metal(const Colour &albedo, double fuzz)
        : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray &rIn, const Hittable::HitRecord &rec,
                 Colour &attenuation, Ray &scattered) const override {
        Vec3 reflected = rIn.dir.reflect(rec.normal);
        reflected   = reflected.unitVector() + (Vec3::randUnitVector() * fuzz);
        scattered   = Ray(rec.p, reflected);
        attenuation = albedo;
        return scattered.dir.dot(rec.normal) > 0;
    }

  private:
    Colour albedo;
    double fuzz;
};

#endif // MATERIAL_H_
