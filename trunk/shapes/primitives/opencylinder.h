#ifndef OPENCYLINDER_H
#define OPENCYLINDER_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// An open cylinder is defined by its extent in the y direction and its radius.
// It is centered on the y axis.
// The classes ConcaveOpenCylinder and ConvexOpenCylinder can inherit from OpenCylinder.
// The classes ConcavePartCylinder and ConvexPartCylinder can in turn inherit from these.

#include "shape.h"

class OpenCylinder: public Shape {
public:
    OpenCylinder(void);
    OpenCylinder(const double bottom, const double top, const double radius);
    OpenCylinder(const OpenCylinder& c);

    virtual OpenCylinder*
    clone (void) const;

    OpenCylinder&
    operator= (const OpenCylinder& rhs);

    virtual
    ~OpenCylinder(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

    /* get_bounding_box by L.B. */
    virtual BBox
    get_bounding_box();

protected:
    double		y0;				// bottom y value
    double		y1;				// top y value
    double		radius;			// radius
    double		inv_radius;  	// one over the radius
};

#endif // OPENCYLINDER_H
