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

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
        auto scatterDirection = record.normalVector + randomUnitVector();

        if (scatterDirection.nearZero()) {
            scatterDirection = record.normalVector;
        }

        scattered = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

class Metal: public Material {
public:
    Metal(const Color& albedo) : albedo(albedo) {}
    bool scatter(const Ray &rayIn, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        Vector3D reflected = reflect(rayIn.direction(), record.normalVector);
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return true;
    }
private:
    Color albedo;
};

#endif //MATERIAL_H
