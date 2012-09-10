#include "constants.h"
#include "point2d.h"

#include "thinlens.h"
#include <math.h>

ThinLens::ThinLens()
    : Camera(),
      sampler_ptr(NULL),
      zoom(1.0),
      d(500),
      lens_radius(1.0),
      f(1.0)
{}

ThinLens::ThinLens(const ThinLens &t)
    : Camera(t),
      zoom(t.zoom),
      d(t.d),
      lens_radius(t.lens_radius),
      f(t.f)
{
    if(t.sampler_ptr){
        sampler_ptr = t.sampler_ptr->clone();
    }
    else{
        sampler_ptr = NULL;
    }
}

Camera*
ThinLens::clone(void) const{
    return (new ThinLens(*this));
}

ThinLens&
ThinLens::operator =(const ThinLens &rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Camera::operator= (rhs);

    lens_radius = rhs.lens_radius;
    d = rhs.d;
    f = rhs.f;
    zoom = rhs.zoom;

    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }

    return (*this);
}

ThinLens::~ThinLens(void)
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void
ThinLens::set_sampler(Sampler *sp)
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    sampler_ptr = sp;
    sampler_ptr->map_samples_to_unit_disk();
}

Vector3D
ThinLens::ray_direction(const Point2D &pixel_point, const Point2D &lens_point) const
{
    Point2D p;
    p.x = pixel_point.x * f / d;
    p.y = pixel_point.y * f / d;

    Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
    dir.normalize();

    return dir;
}

void
ThinLens::render_scene(const Scene &w)
{
    RGBColor L;
    Ray ray;
    ViewPlane vp(w.vp);
    int depth = 0;

    Point2D sp;
    Point2D pp;
    Point2D dp;
    Point2D lp;

    vp.s /= zoom;

    for(int r = 0; r < vp.vres; r++){
        for(int c = 0; c < vp.hres; c++){
            L = black;

            for(int n = 0; n < vp.num_samples; n++){
                sp = vp.sampler_ptr->sample_unit_square();
                pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
                pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);

                dp = sampler_ptr->sample_unit_square();
                lp = dp * lens_radius;

                ray.o = eye + lp.x * u + lp.y * v;
                ray.d = ray_direction(pp,lp);
                L += w.tracer_ptr->trace_ray(ray,depth);
            }

            L /= vp.num_samples;
            L *= exposure_time;
            w.display_pixel(r, c, L);
        }
    }
}
