#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "colour.hpp"
#include "hittable.hpp"
#include "ray.hpp"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &rIn, const Hittable::HitRecord &rec,
                         Colour &attenuation, Ray &scattered) const {
        return false;
    }
};

#endif // MATERIAL_H_
