#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include "hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable {
  public:
    std::vector<std::shared_ptr<Hittable>> objs;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> obj) { this->add(obj); }

    void clear() { this->objs.clear(); }

    void add(std::shared_ptr<Hittable> obj) { objs.push_back(obj); }

    bool hit(const Ray &r, Interval t, HitRecord &rec) const override {
        HitRecord tempRec;
        bool      hitAnything = false;
        double    currClosest = t.max;

        for (const auto &obj : objs) {
            if (obj->hit(r, Interval(t.min, currClosest), tempRec)) {
                hitAnything = true;
                currClosest = tempRec.t;
                rec         = tempRec;
            }
        }

        return hitAnything;
    }
};

#endif // HITTABLE_LIST_H_
