#ifndef TRANSPARENT_H
#define TRANSPARENT_H

/* by L.B. */
#include "phong.h"
#include "perfectspecular.h"
#include "perfecttransmitter.h"

class Transparent: public Phong {
public:
    // constructors, etc ...
    Transparent(void);
    Transparent(const Transparent& t);

    Transparent&
    operator= (const Transparent& rhs);

    virtual Transparent*
    clone(void) const;

    ~Transparent(void);

    void
    set_ior(const float f);

    void
    set_kt(const float f);

    void
    set_kr(const float f);

    virtual RGBColor
    shade(ShadeRec& sr);

private:
    PerfectSpecular* 	reflective_brdf;
    PerfectTransmitter* specular_btdf;
};

inline void
Transparent::set_ior(const float f) {
    specular_btdf->set_ior(f);
}

inline void
Transparent::set_kt(const float f) {
    specular_btdf->set_kt(f);
}

inline void
Transparent::set_kr(const float f) {
    reflective_brdf->set_kr(f);
}

#endif // TRANSPARENT_H
