#ifndef BRDF_H
#define BRDF_H

// This file contains the declaration of the base class BRDF

#include <math.h>

#include "rgbcolor.h"
#include "vector3d.h"
#include "shaderec.h"
#include "sampler.h"

class BRDF {
public:
    BRDF(void);
    BRDF(const BRDF& brdf);

    virtual BRDF*
    clone(void)const = 0;

    BRDF&
    operator= (const BRDF& rhs);

    virtual
    ~BRDF(void);

    void
    set_sampler(Sampler* sPtr);

    virtual RGBColor
    f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    // parameter wi in this function is used to return the direction wi
    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

    virtual RGBColor
    rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    Sampler* sampler_ptr;		// for indirect illumination
};

#endif // BRDF_H
