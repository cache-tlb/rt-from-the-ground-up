#include "constants.h"
#include "point3d.h"
#include "vector3d.h"
#include "orthographic.h"
#include <math.h>

Orthographic::Orthographic()
    :   Camera()
{}

Orthographic::Orthographic(const Orthographic& oh)
    :   Camera(oh)
{}

Camera*
Orthographic::clone(void) const
{
    return (new Orthographic(*this));
}

Orthographic&
Orthographic::operator =(const Orthographic& rhs)
{
    if(this == &rhs){
        return (*this);
    }

    Camera::operator =(rhs);

    return (*this);
}

Orthographic::~Orthographic(void){}

void
Orthographic::render_scene(const Scene &w)
{
    RGBColor L = black;
    Ray ray;
    int 		hres 	= w.vp.hres;
    int 		vres 	= w.vp.vres;
    float		s		= w.vp.s;
    float		zw		= 100.0;				// hardwired in

    ray.d = Vector3D(0, 0, -1);

    for (int r = 0; r < vres; r++){			// up
        for (int c = 0; c < hres; c++) {	// across
            ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
            L = w.tracer_ptr->trace_ray(ray,3);
            L *= exposure_time;
            w.display_pixel(r, c, L);
        }
    }

}
