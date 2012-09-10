#include "ambientoccluder.h"
#include "scene.h"

AmbientOccluder::AmbientOccluder(void)
    : Light(),
      ls(1.0),
      color(1.0),
      min_amount(0.0),
      u(1, 0, 0),
      v(0, 1, 0),
      w(0, 0, 1),
      sampler_ptr(NULL)
{}

AmbientOccluder::AmbientOccluder(const AmbientOccluder &ao)
    : Light(),
      ls(ao.ls),
      color(ao.color),
      min_amount(ao.min_amount),
      u(ao.u),
      v(ao.v),
      w(ao.w)
{
    if(ao.sampler_ptr){
        sampler_ptr = ao.sampler_ptr->clone();
    }
    else{
        sampler_ptr = NULL;
    }
}

Light*
AmbientOccluder::clone(void) const {
    return (new AmbientOccluder(*this));
}

AmbientOccluder&
AmbientOccluder::operator =(const AmbientOccluder& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Light::operator=(rhs);

    ls = rhs.ls;
    color = rhs.color;
    min_amount = rhs.min_amount;
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;

    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }
    else{
        sampler_ptr = NULL;
    }

    return (*this);
}

AmbientOccluder::~AmbientOccluder()
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void
AmbientOccluder::set_sampler(Sampler* s_ptr) {
    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    sampler_ptr = s_ptr;
    sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D
AmbientOccluder::get_direction(ShadeRec& sr) {
    Point3D sp = sampler_ptr->sample_hemisphere();
    return (sp.x * u + sp.y * v + sp.z * w);
}

bool
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float 	t;
    int 	num_objects = sr.w.objects.size();

    for (int j = 0; j < num_objects; j++){
        if (sr.w.objects[j]->shadow_hit(ray, t)){
            return (true);
        }
    }

    return (false);
}

RGBColor
AmbientOccluder::L(ShadeRec& sr) {
    w = sr.normal;
    v = w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
    v.normalize();
    u = v ^ w;

    Ray shadow_ray;
    shadow_ray.o = sr.hit_point;
    shadow_ray.d = get_direction(sr);

    if (in_shadow(shadow_ray, sr))
        return (min_amount * ls * color);
    else
        return (ls * color);
}
