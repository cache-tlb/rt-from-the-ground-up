#ifndef SV_MATTE_H
#define SV_MATTE_H

#include "material.h"
#include "sv_lambertian.h"
#include <iostream>

class SV_Matte: public Material {
public:
    // consructors, etc ...
    /* by L.B. */
    SV_Matte();
    SV_Matte(const SV_Matte& m);

    virtual Material*
    clone(void) const;

    SV_Matte&
    operator= (const SV_Matte& rhs);

    virtual
    ~SV_Matte(void);

    void
    set_ka(const float k);

    void
    set_kd(const float k);

    void
    set_cd(const Texture* t_ptr);

    virtual RGBColor
    shade(ShadeRec& s);

private:
    SV_Lambertian*	ambient_brdf;
    SV_Lambertian*	diffuse_brdf;
};

inline void
SV_Matte::set_cd(const Texture* t_ptr) {
    ambient_brdf->set_cd(t_ptr);
    diffuse_brdf->set_cd(t_ptr);
}

// ------ set_ka by L.B.
inline void
SV_Matte::set_ka(const float k) {
    ambient_brdf->set_ka(k);
}

// ------ set_kd by L.B.
inline void
SV_Matte::set_kd(const float k) {
    diffuse_brdf->set_kd(k);
}

#endif // SV_MATTE_H
