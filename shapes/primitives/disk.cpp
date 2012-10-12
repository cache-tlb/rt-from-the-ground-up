#include "disk.h"

/* by L.B. */

// ------  default constructor
Disk::Disk(void)
    : Shape(),
      center(0.0),
      normal(0, 1, 0),
      r_squared(1.0)
{}

// ------  constructor
Disk::Disk(const Point3D& point, const Normal& n, const float radius)
    : Shape(),
      center(point),
      normal(n),
      r_squared(radius*radius)
{
        normal.normalize();
}

// ------ copy constructor
Disk::Disk(const Disk& disk)
    : Shape(disk),
      center(disk.center),
      normal(disk.normal),
      r_squared(disk.r_squared)
{}

// ------ clone
Disk*
Disk::clone(void) const {
    return (new Disk(*this));
}

// ------ assignment operator
Disk&
Disk::operator= (const Disk& rhs)	{

    if (this == &rhs){
        return (*this);
    }

    Shape::operator= (rhs);

    center = rhs.center;
    normal = rhs.normal;
    r_squared = rhs.r_squared;

    return (*this);
}

// ------ destructor
Disk::~Disk(void)
{}

bool
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

    double t = (center - ray.o) * normal / (ray.d * normal);

    if (t <= kEpsilon)
        return (false);

    Point3D p = ray.o + t * ray.d;

    if (center.d_squared(p) < r_squared) {
        tmin 				= t;
        sr.normal 			= normal;
        sr.local_hit_point	= p;
        return (true);
    }
    else
        return (false);
}

bool
Disk::shadow_hit(const Ray &ray, float &tmin) const {
    double t = (center - ray.o) * normal / (ray.d * normal);

    if (t <= kEpsilon){
        return (false);
    }

    Point3D p = ray.o + t * ray.d;

    if (center.d_squared(p) < r_squared) {
        tmin = t;
        return (true);
    }
    else{
        return (false);
    }
}
