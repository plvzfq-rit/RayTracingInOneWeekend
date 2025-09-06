//
// Created by James Christian on 06/09/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "Hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

#endif //MATERIAL_H
