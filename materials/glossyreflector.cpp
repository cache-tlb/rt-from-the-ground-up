#include "glossyreflector.h"

// ------ default constructor
GlossyReflector::GlossyReflector()
    :	Phong(),
        glossy_specular_brdf(new GlossySpecular)
{}

// ------ copy constructor
GlossyReflector::GlossyReflector(const GlossyReflector& g)
    : 	Phong(g) {

    if(g.glossy_specular_brdf){
        glossy_specular_brdf = g.glossy_specular_brdf->clone();
    }
    else{
        glossy_specular_brdf = NULL;
    }
}

// ------ assignment operator
GlossyReflector&
GlossyReflector::operator= (const GlossyReflector& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Phong::operator=(rhs);

    if (glossy_specular_brdf) {
        delete glossy_specular_brdf;
        glossy_specular_brdf = NULL;
    }

    if (rhs.glossy_specular_brdf){
        glossy_specular_brdf = rhs.glossy_specular_brdf->clone();
    }

    return (*this);
}

// ------ clone
GlossyReflector*
GlossyReflector::clone(void) const {
    return (new GlossyReflector(*this));
}

// ------ destructor
GlossyReflector::~GlossyReflector(void) {
    if (glossy_specular_brdf) {
        delete glossy_specular_brdf;
        glossy_specular_brdf = NULL;
    }
}

RGBColor
GlossyReflector::shade(ShadeRec &sr) {
    RGBColor 	L(Phong::shade(sr));  // direct illumination
    Vector3D 	wo(-sr.ray.d);
    Vector3D 	wi;
    float		pdf;
    RGBColor 	fr(glossy_specular_brdf->sample_f(sr, wo, wi, pdf));
    Ray 		reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf;

    return L;
}

RGBColor
GlossyReflector::area_light_shade(ShadeRec& sr) {
    RGBColor 	L(Phong::area_light_shade(sr));  // direct illumination
    Vector3D 	wo(-sr.ray.d);
    Vector3D 	wi;
    float		pdf;
    RGBColor 	fr(glossy_specular_brdf->sample_f(sr, wo, wi, pdf));
    Ray 		reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf;

    return (L);
}
