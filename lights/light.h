#ifndef LIGHT_H
#define LIGHT_H

#include "vector3d.h"
#include "rgbcolor.h"
#include "ray.h"

class ShadeRec;

// ------ class Light
class Light {
public:
    Light(void);
    Light(const Light& ls);

    Light&
    operator= (const Light& rhs);

    virtual Light*
    clone(void) const = 0;

    virtual
    ~Light(void);

    void
    set_shadows(bool _shadows);

    virtual Vector3D
    get_direction(ShadeRec& sr) = 0;

    virtual RGBColor
    L(ShadeRec& sr) = 0;

    /* not sure for casts_shadows */
    bool
    casts_shadows();

    virtual bool
    in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual float
    G(const ShadeRec& sr) const;

    virtual float
    pdf(const ShadeRec& sr) const;

protected:
    bool shadows;
};

inline void
Light::set_shadows(bool _shadows)
{
    shadows = _shadows;
}

inline bool
Light::casts_shadows()
{
    return shadows;
}

#endif // LIGHT_H
