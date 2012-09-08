#ifndef PERFECTTRANSMITTER_H
#define PERFECTTRANSMITTER_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this implements perfect specular transmission for transparent materials

#include "btdf.h"

class PerfectTransmitter: public BTDF {
public:
    PerfectTransmitter(void);
    PerfectTransmitter(const PerfectTransmitter& pt);

    virtual PerfectTransmitter*
    clone(void) const;

    ~PerfectTransmitter(void);

    PerfectTransmitter&
    operator= (const PerfectTransmitter& rhs);

    void
    set_kt(const float k);

    void
    set_ior(const float eta);

    bool
    tir(const ShadeRec& sr) const;

    virtual RGBColor
    f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

    virtual RGBColor
    rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
    float	kt;			// transmission coefficient
    float	ior;		// index of refraction
};

// ------ set_kt
inline void
PerfectTransmitter::set_kt(const float k) {
    kt = k;
}

// ------ set_ior
inline void
PerfectTransmitter::set_ior(const float eta) {
    ior = eta;
}

#endif // PERFECTTRANSMITTER_H
