#ifndef FRESNELREFLECTOR_H
#define FRESNELREFLECTOR_H

/* by L.B. */

#include "brdf.h"

class FresnelReflector : public BRDF {
public:
    FresnelReflector(void);
    FresnelReflector(const FresnelReflector& pt);

    virtual FresnelReflector*
    clone(void) const;

    ~FresnelReflector(void);

    FresnelReflector&
    operator= (const FresnelReflector& rhs);

    float
    fresnel(const ShadeRec& sr) const;

    virtual RGBColor
    sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wr) const;

    void
    set_eta_in(const float e);

    void
    set_eta_out(const float e);

private:
    float eta_in, eta_out;
};

inline void
FresnelReflector::set_eta_in(const float e){
    eta_in = e;
}

inline void
FresnelReflector::set_eta_out(const float e){
    eta_out = e;
}

#endif // FRESNELREFLECTOR_H
