#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
#include "vector3d.h"
#include "rgbcolor.h"

#include "scene.h"
#include "shaderec.h"

class PointLight : public Light
{
public:
    PointLight(void);
    PointLight(const PointLight& pr);

    virtual Light*
    clone(void) const;

    PointLight&
    operator= (const PointLight& rhs);

    virtual
    ~PointLight(void);

    void
    set_location(const Point3D& loc);

    void
    set_location(float px, float py, float pz);

    void
    scale_radiance(const float b);

    virtual Vector3D
    get_direction(ShadeRec& sr);

    virtual RGBColor
    L(ShadeRec& sr);

    /*not sure*/
    virtual bool
    in_shadow(const Ray &ray, const ShadeRec &sr) const;

private:
    float ls;
    RGBColor color;
    Point3D location;
};

inline void
PointLight::set_location(const Point3D& loc)
{
    location = loc;
}

inline void
PointLight::set_location(float px, float py, float pz)
{
    location.x = px;
    location.y = py;
    location.z = pz;
}

inline void
PointLight::scale_radiance(const float b) {
    ls = b;
}

#endif // POINTLIGHT_H
