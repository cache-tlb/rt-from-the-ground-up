#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "lambertian.h"
#include "glossyspecular.h"

class Phong : public Material
{
public:
    Phong();
    Phong(const Phong& p);

    virtual Material*
    clone(void) const;

    Phong&
    operator =(const Phong& rhs);

    virtual
    ~Phong();

    void
    set_ka(const float k);

    void
    set_kd(const float k);

    void
    set_cd(const RGBColor& c);

    void
    set_cd(const float r, const float g, const float b);

    void
    set_cd(const float c);

    void
    set_ks(const float k);

    void
    set_cs(const RGBColor& c);

    void
    set_cs(const float r, const float g, const float b);

    void
    set_cs(const float c);

    void
    set_exp(const float e);

    virtual RGBColor
    shade(ShadeRec& sr);

    /* L.B. */
    virtual RGBColor
    area_light_shade(ShadeRec &sr);

protected:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    GlossySpecular* specular_brdf;
};

// ------ set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection
inline void
Phong::set_ka(const float ka) {
    ambient_brdf->set_kd(ka);
}

// ------ set_kd
// this also sets Lambertian::kd, but for a different Lambertian object
inline void
Phong::set_kd (const float kd) {
    diffuse_brdf->set_kd(kd);
}

// ------ set_cd
inline void
Phong::set_cd(const RGBColor& c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

// ------ set_cd
inline void
Phong::set_cd(const float r, const float g, const float b) {
    ambient_brdf->set_cd(r, g, b);
    diffuse_brdf->set_cd(r, g, b);
}

// ------ set_cd
inline void
Phong::set_cd(const float c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

// ------ set_ks
inline void
Phong::set_ks(const float k)
{
    specular_brdf->set_ks(k);
}

// ------ set_cs
inline void
Phong::set_cs(const RGBColor &c) {
    specular_brdf->set_cs(c);
}

// ------ set_cs
inline void
Phong::set_cs(const float r, const float g, const float b) {
    specular_brdf->set_cs(r, g, b);
}

// ------ set_cs
inline void
Phong::set_cs(const float c) {
    specular_brdf->set_cs(c);
}

// ------ set_exp
inline void
Phong::set_exp(const float e)
{
    specular_brdf->set_exp(e);
}

#endif // PHONG_H
