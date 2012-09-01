#ifndef BBOX_H
#define BBOX_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "ray.h"
#include "point3d.h"

class BBox {
public:
    double x0, x1, y0, y1, z0, z1;

    BBox(void);
    BBox(	const double x0, const double x1,
            const double y0, const double y1,
            const double z0, const double z1);
    BBox(const Point3D p0, const Point3D p1);
    BBox(const BBox& bbox);

    BBox&
    operator= (const BBox& rhs);

    ~BBox(void);

    bool
    hit(const Ray& ray) const;

    bool
    inside(const Point3D& p) const;
};

#endif // BBOX_H
