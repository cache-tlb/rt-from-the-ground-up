#ifndef SPHERE_H
#define SPHERE_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class Sphere

#include "shape.h"
#include "sampler.h"

// ------ class Sphere

class Sphere: public Shape {
public:
    Sphere(void);   									// Default constructor
    Sphere(Point3D center, double r);					// Constructor
    Sphere(const Sphere& sphere); 						// Copy constructor

    virtual Sphere* 									// Virtual copy constructor
    clone(void) const;

    virtual												// Destructor
    ~Sphere(void);

    Sphere& 											// assignment operator
    operator= (const Sphere& sphere);

    void
    set_center(const Point3D& c);

    void
    set_center(const double x, const double y, const double z);

    void
    set_radius(const double r);

    virtual BBox
    get_bounding_box();

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& s) const;

    virtual bool
    shadow_hit(const Ray& ray, float& tmin) const;

    // added by L.B.
    void
    set_sampler(Sampler *s_ptr);

private:
    Point3D 	center;   			// center coordinates as a point
    double 		radius;				// the radius
    Sampler*    sampler_ptr;

    static const double kEpsilon;   // for shadows and secondary rays
};

inline void
Sphere::set_center(const Point3D& c) {
    center = c;
}

inline void
Sphere::set_center(const double x, const double y, const double z) {
    center.x = x;
    center.y = y;
    center.z = z;
}

inline void
Sphere::set_radius(const double r) {
    radius = r;
}

#endif // SPHERE_H
