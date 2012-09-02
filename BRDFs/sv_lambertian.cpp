#include "sv_lambertian.h"
#include <iostream>

SV_Lambertian::SV_Lambertian()
    : BRDF(),
      kd(0),
      cd(NULL)
{}

SV_Lambertian::SV_Lambertian(const SV_Lambertian &sl)
    : BRDF(sl),
      kd(sl.kd)
{
    if(sl.cd){
        cd = sl.cd->clone();
    }
    else{
        cd = NULL;
    }
}

SV_Lambertian&
SV_Lambertian::operator =(const SV_Lambertian& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    BRDF::operator= (rhs);

    kd = rhs.kd;

    if(cd){
        delete cd;
        cd = NULL;
    }

    if(rhs.cd){
        cd = rhs.cd->clone();
    }

    return (*this);
}

SV_Lambertian::~SV_Lambertian()
{
    if(cd){
        delete cd;
        cd = NULL;
    }
}

SV_Lambertian*
SV_Lambertian::clone() const{
    return (new SV_Lambertian(*this));
}

void
SV_Lambertian::set_cd(const Texture *texture_ptr)
{
    if(cd){
        delete cd;
        cd = NULL;
    }
    if(texture_ptr){
        cd = texture_ptr->clone();
    }
}

RGBColor
SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return (kd * cd->get_color(sr));
}

RGBColor
SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return (kd * cd->get_color(sr) * invPI);
}

RGBColor
SV_Lambertian::sample_f(const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi) const {
    //std::cout << "not implement yet" << std::endl;
    return (kd * cd->get_color(sr) * invPI);
}
