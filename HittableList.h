//
// Created by James Christian on 06/09/2025.
//

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hitInTimeRange(const Ray& ray, Interval timeInterval, HitRecord& record) const override {
        HitRecord tempRecord;
        bool hitAny = false;
        auto closestSoFar = timeInterval.max;
        for (auto& object : objects) {
            if (object->hitInTimeRange(ray, Interval(timeInterval.min, closestSoFar), tempRecord)) {
                hitAny = true;
                closestSoFar = tempRecord.time;
                record = tempRecord;
            }
        }

        return hitAny;
    }
};

#endif //HITTABLELIST_H
