#include "sv_matte.h"

SV_Matte::SV_Matte()
    : Material(),
      ambient_brdf(new SV_Lambertian),
      diffuse_brdf(new SV_Lambertian)
{}

SV_Matte::SV_Matte(const SV_Matte &m)
    : Material()
{
    if(m.ambient_brdf){
        ambient_brdf = (SV_Lambertian*)m.ambient_brdf->clone();
    }
    else {
        ambient_brdf = NULL;
    }

    if(m.diffuse_brdf){
        diffuse_brdf = (SV_Lambertian*)m.diffuse_brdf->clone();
    }
    else{
        diffuse_brdf = NULL;
    }
}

Material*
SV_Matte::clone(void) const
{
    return (new SV_Matte(*this));
}

SV_Matte&
SV_Matte::operator =(const SV_Matte& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Material::operator=(rhs);

    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if (rhs.ambient_brdf){
        ambient_brdf = (SV_Lambertian*)rhs.ambient_brdf->clone();
    }

    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }

    if (rhs.diffuse_brdf){
        diffuse_brdf = (SV_Lambertian*)rhs.diffuse_brdf->clone();
    }

    return (*this);
}

SV_Matte::~SV_Matte()
{
    if(ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if(diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
}

RGBColor
SV_Matte::shade(ShadeRec& sr) {
    Vector3D 	wo 			= -sr.ray.d;
    RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    int 		num_lights 	= sr.w.lights.size();

    for (int j = 0; j < num_lights; j++) {
        Light* light_ptr = sr.w.lights[j];
        Vector3D wi = light_ptr->get_direction(sr);
        wi.normalize();
        float ndotwi = sr.normal * wi;
        float ndotwo = sr.normal * wo;

        if (ndotwi > 0.0 && ndotwo > 0.0) {
            bool in_shadow = false;

            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadow_ray(sr.hit_point, wi);
                in_shadow = light_ptr->in_shadow(shadow_ray, sr);
            }

            if (!in_shadow)
                L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
        }
    }

    return (L);
}
