#ifndef FRESNELTRANSMITTER_H
#define FRESNELTRANSMITTER_H

/* by L.B. */

#include "btdf.h"

class FresnelTransmitter : public BTDF
{
public:
    FresnelTransmitter(void);
    FresnelTransmitter(const FresnelTransmitter& ft);

    virtual FresnelTransmitter*
    clone(void) const;

    ~FresnelTransmitter(void);

    FresnelTransmitter&
    operator= (const FresnelTransmitter& rhs);

    bool
    tir(const ShadeRec& sr) const;

    float
    fresnel(const ShadeRec& sr) const;

    virtual RGBColor
    sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt) const;

    void
    set_eta_out(const float e);

    void
    set_eta_in(const float e);

private:
    float eta_out, eta_in;

};

inline void
FresnelTransmitter::set_eta_in(const float e){
    eta_in = e;
}

inline void
FresnelTransmitter::set_eta_out(const float e) {
    eta_out = e;
}

#endif // FRESNELTRANSMITTER_H
