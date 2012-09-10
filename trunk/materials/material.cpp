#include "material.h"

// ------ default constructor
Material::Material(void) {}

// ------ copy constructor
Material::Material(const Material& m) {}


// ------ assignment operator
Material&
Material::operator= (const Material& rhs) {
    if (this == &rhs){
        return (*this);
    }

    return (*this);
}

// ------ destructor
Material::~Material(void)
{}

// ------ shade
RGBColor
Material::shade(ShadeRec& sr) {
    return (black);
}

// ------ get_Le
RGBColor
Material::get_Le(ShadeRec &sr) const {
    return black;
}

// ------ area_light_shade
RGBColor
Material::area_light_shade(ShadeRec &sr) {
    return shade(sr);
}

// ------ path_shade
RGBColor
Material::path_shade(ShadeRec& sr) {
    return shade(sr);
}

// ------ golbal_shade
RGBColor
Material::global_shade(ShadeRec &sr) {
    return shade(sr);
}
