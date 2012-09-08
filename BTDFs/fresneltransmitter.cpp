/* by L.B. */

#include "fresneltransmitter.h"

// ------ default constructor
FresnelTransmitter::FresnelTransmitter(void)
    : BTDF(),
      eta_out(1.0),
      eta_in(1.0)
{}

// ------ copy constructor
FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& ft)
    : BTDF(ft),
      eta_out(ft.eta_out),
      eta_in(ft.eta_in)
{}

// ------ clone
FresnelTransmitter*
FresnelTransmitter::clone(void) const {
    return (new FresnelTransmitter(*this));
}

// ------ destructor
FresnelTransmitter::~FresnelTransmitter(void) {}

// ------ assignment operator
FresnelTransmitter&
FresnelTransmitter::operator= (const FresnelTransmitter& rhs) {
    if (this == &rhs){
        return (*this);
    }

    eta_out = rhs.eta_out;
    eta_in = rhs.eta_in;

    return (*this);
}

// ------ fresnel
// copy from sample code(fresnel reflector)
float
FresnelTransmitter::fresnel(const ShadeRec& sr) const {
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
// by L.B.
RGBColor
FresnelTransmitter::sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt) const
{
    Normal n(sr.normal);
    float cos_thetai = n * wo;
    float eta;

    if (cos_thetai < 0.0) {			// transmitted ray is outside
        cos_thetai = -cos_thetai;
        n = -n;  					// reverse direction of normal
        eta = eta_out / eta_in; 			// invert ior
    }
    else{
        eta = eta_in / eta_out;
    }

    float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
    float cos_theta2 = sqrt(temp);
    wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

    return ((1.0-fresnel(sr)) * white / fabs(sr.normal * wt));
}

// ------ tir
// by L.B.
bool FresnelTransmitter::tir(const ShadeRec &sr) const{
    Normal normal(sr.normal);
    float ndotd = -normal * sr.ray.d;
    float eta;

    if (ndotd < 0.0) {
        eta = eta_out / eta_in;
    }
    else
        eta = eta_in / eta_out;

    // ndotd is cos_theta

    return (1.0 - (1.0 - ndotd * ndotd) / (eta * eta) < 0.0);
}
