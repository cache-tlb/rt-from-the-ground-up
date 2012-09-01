#include "emissive.h"

Emissive::Emissive(void)
    : Material(),
      ls(1.0),
      ce()
{}

Emissive::Emissive(const Emissive &e)
    : Material(e),
      ls(e.ls),
      ce(e.ce)
{}

Material*
Emissive::clone(void) const
{
    return (new Emissive(*this));
}

Emissive&
Emissive::operator =(const Emissive& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Material::operator=(rhs);

    ls = rhs.ls;
    ce = rhs.ce;

    return (*this);
}

Emissive::~Emissive() {}

RGBColor
Emissive::get_Le(ShadeRec &sr) const
{
    return ls*ce;
}

RGBColor
Emissive::shade(ShadeRec &sr) {
    return black;
}

RGBColor
Emissive::area_light_shade(ShadeRec& sr) {
    if (-sr.normal * sr.ray.d > 0.0)
        return (ls * ce);
    else
        return (black);
}
