#ifndef DIELECTRIC_H
#define DIELECTRIC_H

/* by L.B. */

#include "phong.h"
#include "fresnelreflector.h"
#include "fresneltransmitter.h"

class Dielectric : public Phong
{
public:
    Dielectric(void);
    Dielectric(const Dielectric& d);

    Dielectric&
    operator= (const Dielectric& rhs);

    virtual Dielectric*
    clone(void) const;

    ~Dielectric(void);

    virtual RGBColor
    shade(ShadeRec& s);

    void
    set_cf_in(const RGBColor &c);

    void
    set_cf_in(const float r, const float g, const float b);

    void
    set_cf_out(const RGBColor &c);

    void
    set_cf_out(const float r, const float g, const float b);

    void
    set_eta_in(const float e);

    void
    set_eta_out(const float e);

private:
    RGBColor 			cf_in;			// interior filter color
    RGBColor 			cf_out;			// exterior filter color

    FresnelReflector*	fresnel_brdf;
    FresnelTransmitter*	fresnel_btdf;

};

inline void
Dielectric::set_cf_in(const RGBColor &c){
    cf_in = c;
    Phong::set_cd(c);
}

inline void
Dielectric::set_cf_in(const float r, const float g, const float b) {
    cf_in.r = r; cf_in.g = g; cf_in.b = b;
    Phong::set_cd(r,g,b);
}

inline void
Dielectric::set_cf_out(const RGBColor &c){
    cf_out = c;
}

inline void
Dielectric::set_cf_out(const float r, const float g, const float b) {
    cf_out.r = r; cf_out.g = g; cf_out.b = b;
}

inline void
Dielectric::set_eta_in(const float e) {
    fresnel_brdf->set_eta_in(e);
    fresnel_btdf->set_eta_in(e);
}

inline void
Dielectric::set_eta_out(const float e) {
    fresnel_brdf->set_eta_out(e);
    fresnel_btdf->set_eta_out(e);
}

#endif // DIELECTRIC_H
