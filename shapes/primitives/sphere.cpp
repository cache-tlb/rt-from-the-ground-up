// This file contains the definition of the class sphere

#include "sphere.h"
#include <math.h>

const double Sphere::kEpsilon = 0.001;

// ------ default constructor
Sphere::Sphere(void)
    : 	Shape(),
        center(0.0),
        radius(1.0),
      sampler_ptr(NULL)
{}

// ------ constructor
Sphere::Sphere(Point3D c, double r)
    : 	Shape(),
        center(c),
        radius(r),
      sampler_ptr(NULL)
{}

// ------ clone
Sphere*
Sphere::clone(void) const {
    return (new Sphere(*this));
}

// ------ copy constructor
Sphere::Sphere (const Sphere& sphere)
    : 	Shape(sphere),
        center(sphere.center),
        radius(sphere.radius)
{
    if(sphere.sampler_ptr){
        sampler_ptr = sphere.sampler_ptr->clone();
    }
    else{
        sampler_ptr = NULL;
    }
}

// ------ assignment operator
Sphere&
Sphere::operator= (const Sphere& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Shape::operator= (rhs);

    center 	= rhs.center;
    radius	= rhs.radius;

    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }

    return (*this);
}

// ------ destructor
Sphere::~Sphere(void)
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

BBox
Sphere::get_bounding_box() {
    return BBox(center.x - radius, center.x + radius,
                center.y - radius, center.y + radius,
                center.z - radius, center.z + radius);
}

// ------ hit
bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double 		t;
    Vector3D	temp 	= ray.o - center;
    double 		a 		= ray.d * ray.d;
    double 		b 		= 2.0 * temp * ray.d;
    double 		c 		= temp * temp - radius * radius;
    double 		disc	= b * b - 4.0 * a * c;

    if (disc < 0.0){
        return(false);
    }
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal 	 = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal   = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }
    }

    return (false);
}

bool
Sphere::shadow_hit(const Ray& ray, float& tmin) const {
    double 		t;
    Vector3D	temp 	= ray.o - center;
    double 		a 		= ray.d * ray.d;
    double 		b 		= 2.0 * temp * ray.d;
    double 		c 		= temp * temp - radius * radius;
    double 		disc	= b * b - 4.0 * a * c;

    if (disc < 0.0){
        return(false);
    }
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }
    }

    return (false);
}

void
Sphere::set_sampler(Sampler *s_ptr) {
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    sampler_ptr = s_ptr;
    sampler_ptr->map_samples_to_sphere();
}
