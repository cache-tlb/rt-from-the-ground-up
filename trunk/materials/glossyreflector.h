#ifndef GLOSSYREFLECTOR_H
#define GLOSSYREFLECTOR_H

#include "glossyspecular.h"
#include "phong.h"

class GlossyReflector: public Phong {
public:
    // constructors etc ...
    GlossyReflector();
    GlossyReflector(const GlossyReflector& g);

    GlossyReflector&
    operator= (const GlossyReflector& rhs);

    virtual GlossyReflector*
    clone(void) const;

    ~GlossyReflector();

    void
    set_samples(const int num_samples, const float exp);

    void
    set_kr(const float k);

    void
    set_exponent(const float exp);

    void
    set_cr(const RGBColor& c);

    void
    set_cr(const float r, const float g, const float b);

    void
    set_cr(const float c);

    virtual RGBColor
    shade(ShadeRec &sr);

    virtual RGBColor
    area_light_shade(ShadeRec& sr);

private:
    GlossySpecular* glossy_specular_brdf;
};

inline void
GlossyReflector::set_samples(const int num_samples, const float exp) {
    glossy_specular_brdf->set_samples(num_samples, exp);
}

inline void
GlossyReflector::set_kr(const float k) {
    glossy_specular_brdf->set_ks(k);
}

inline void
GlossyReflector::set_exponent(const float exp) {
    glossy_specular_brdf->set_exp(exp);
}

inline void
GlossyReflector::set_cr(const float r, const float g, const float b) {
    glossy_specular_brdf->set_cs(r, g, b);
}

inline void
GlossyReflector::set_cr(const RGBColor &c) {
    glossy_specular_brdf->set_cs(c);
}

inline void
GlossyReflector::set_cr(const float c) {
    glossy_specular_brdf->set_cs(c);
}

#endif // GLOSSYREFLECTOR_H
