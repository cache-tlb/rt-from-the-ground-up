#ifndef PLANE_H
#define PLANE_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "shape.h"

// ------ class Plane

class Plane: public Shape {
public:
    Plane(void);   												// default constructor
    Plane(const Point3D& point, const Normal& normal);			// constructor
    Plane(const Plane& plane); 									// copy constructor

    virtual Plane* 												// virtual copy constructor
    clone(void) const;

    Plane& 														// assignment operator
    operator= (const Plane& rhs);

    virtual														// destructor
    ~Plane(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

private:
    Point3D 	a;   				// point through which plane passes
    Normal 		n;					// normal to the plane

    static const double kEpsilon;   // for shadows and secondary rays
};

#endif // PLANE_H
