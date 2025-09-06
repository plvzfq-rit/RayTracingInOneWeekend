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
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1? fuzz : 1) {}
    bool scatter(const Ray &rayIn, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        Vector3D reflected = reflect(rayIn.direction(), record.normalVector);
        reflected = normalize(reflected) + (fuzz * randomUnitVector());
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), record.normalVector) > 0);
    }
private:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material {
    public:
    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray &rayIn, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = record.isFrontFace? (1.0 / refractionIndex) : refractionIndex;

        Vector3D unitDirection = normalize(rayIn.direction());
        Vector3D refracted = refract(unitDirection, record.normalVector, ri);

        scattered = Ray(record.point, refracted);
        return true;
    }
private:
    double refractionIndex;
};

#endif //MATERIAL_H
