#ifndef AXISALIGNEDBOX_H
#define AXISALIGNEDBOX_H

// 	writen by Bin Liu.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "shape.h"

class AxisAlignedBox : public Shape
{
public:
    AxisAlignedBox(void);
    AxisAlignedBox(const Vector3D& p1, const Vector3D& p2);
    AxisAlignedBox(const AxisAlignedBox& a);

    virtual AxisAlignedBox*
    clone(void) const;

    AxisAlignedBox&
    operator= (const AxisAlignedBox& rhs);

    virtual
    ~AxisAlignedBox(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

protected:
    double x0, x1, y0, y1, z0, z1;
};

typedef AxisAlignedBox Box;

#endif // AXISALIGNEDBOX_H
