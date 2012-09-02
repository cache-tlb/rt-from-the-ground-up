#ifndef SV_LAMBERTIAN_H
#define SV_LAMBERTIAN_H

#include "brdf.h"
#include "texture.h"

class SV_Lambertian: public BRDF {
public:
    // constructors, etc ...
    /* by L.B. */
    SV_Lambertian();
    SV_Lambertian(const SV_Lambertian& sl);

    virtual SV_Lambertian*
    clone() const;

    ~SV_Lambertian();

    SV_Lambertian&
    operator =(const SV_Lambertian& rhs);

    void
    set_ka(const float k);

    void
    set_kd(const float k);

    void
    set_cd(const Texture *texture_ptr);

    //----------------//
    virtual RGBColor
    rho(const ShadeRec& sr, const Vector3D& wo) const;

    virtual RGBColor
    f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

private:
    float		kd;
    Texture* 	cd;
};

inline void
SV_Lambertian::set_ka(const float k) {
    kd = k;
}

inline void
SV_Lambertian::set_kd(const float k) {
    kd = k;
}

#endif // SV_LAMBERTIAN_H
