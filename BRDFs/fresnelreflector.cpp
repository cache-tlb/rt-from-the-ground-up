/* by L.B. */

#include "fresnelreflector.h"

// ------ default constructor
FresnelReflector::FresnelReflector(void)
    : 	BRDF(),
        eta_in(1.0),
        eta_out(1.0)
{}

// ------ copy constructor
FresnelReflector::FresnelReflector(const FresnelReflector& fr)
    : 	BRDF(fr),
        eta_in(fr.eta_in),
        eta_out(fr.eta_out)
{}

// ------ clone
FresnelReflector*
FresnelReflector::clone(void) const{
    return (new FresnelReflector(*this));
}

// ------ destructor
FresnelReflector::~FresnelReflector(void) {}

// ------ assignment operator
FresnelReflector&
FresnelReflector::operator= (const FresnelReflector& rhs) {
    if (this == &rhs){
        return (*this);
    }

    eta_in = rhs.eta_in;
    eta_out = rhs.eta_out;

    return (*this);
}

// ------ fresnel
// from sample code
float
FresnelReflector::fresnel(const ShadeRec& sr) const {
    Normal normal(sr.normal);
    float ndotd = -normal * sr.ray.d;
    float eta;

    if (ndotd < 0.0) {
        normal = -normal;
        eta = eta_out / eta_in;
    }
    else
        eta = eta_in / eta_out;

    float cos_theta_i 		= -normal * sr.ray.d;
    float temp 				= 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
    float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
    float r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
    float r_perpendicular 	= (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
    float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

    return (kr);
}

// ------ sample_f
// from sample code
RGBColor
FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const {
    float ndotwo = sr.normal * wo;
    wr = -wo + 2.0 * sr.normal * ndotwo;
    return (fresnel(sr) * white / fabs(sr.normal * wr));
}
