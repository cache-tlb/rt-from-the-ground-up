#ifndef AMBIENTOCCLUDER_H
#define AMBIENTOCCLUDER_H

/* by L.B. */

#include "light.h"
#include "sampler.h"
#include "shaderec.h"

class AmbientOccluder: public Light {
public:
    AmbientOccluder(void);
    AmbientOccluder(const AmbientOccluder& ao);

    virtual Light*
    clone(void) const;

    AmbientOccluder&
    operator= (const AmbientOccluder& rhs);

    virtual
    ~AmbientOccluder(void);

    void
    scale_radiance(const float s);

    void
    set_min_amount(const float f);

    void
    set_sampler(Sampler* s_ptr);

    virtual Vector3D
    get_direction(ShadeRec& sr);

    virtual bool
    in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual RGBColor
    L(ShadeRec& sr);

private:
    float		ls;
    RGBColor	color;
    float 		min_amount;
    Vector3D 	u, v, w;
    Sampler*	sampler_ptr;
};

inline void
AmbientOccluder::scale_radiance(const float s) {
    ls = s;
}

inline void
AmbientOccluder::set_min_amount(const float f) {
    min_amount = f;
}

#endif // AMBIENTOCCLUDER_H
