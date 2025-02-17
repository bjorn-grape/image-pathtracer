#pragma once
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>

#include "Light.hh"

class PointLight : public Light {
public:
    PointLight(const Vector3D<float> &position, float radius);

    PointLight(float intensity, const Vector3D<float> &color,
               const Vector3D<float> &position, float radius);

    PointLight() = default;

    const Vector3D<float> &getPosition() const;

    void setPosition(const Vector3D<float> &position);


    float getRadius() const;

    void setRadius(float radius);

    friend class cereal::access;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Light>(this), CEREAL_NVP(radius_));
    }

private:
    Vector3D<float> position;
    float radius_;
};


