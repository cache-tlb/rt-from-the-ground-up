#ifndef TRIANGLE_H
#define TRIANGLE_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// this is the triangle discussed in Section 19.3

#include "shape.h"

class Triangle: public Shape {
public:
    Triangle(void);
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

    virtual Triangle*
    clone(void) const;

    Triangle(const Triangle& triangle);

    ~Triangle(void);

    Triangle&
    operator= (const Triangle& rhs);

    virtual BBox
    get_bounding_box(void);

    void
    compute_normal(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray& ray, double& tmin) const;

private:
    Point3D	v0, v1, v2;
    Normal	normal;
};

#endif // TRIANGLE_H
