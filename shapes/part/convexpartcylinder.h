#ifndef CONVEXPARTCYLINDER_H
#define CONVEXPARTCYLINDER_H

/* by L.B. */

#include "shape.h"

class ConvexPartCylinder : public Shape
{
public:
    ConvexPartCylinder(void);
    ConvexPartCylinder(const double bottom, const double top, const double r,
                       double phi1, double phi2);
    ConvexPartCylinder(const ConvexPartCylinder& c);

    virtual ConvexPartCylinder*
    clone (void) const;

    ConvexPartCylinder&
    operator= (const ConvexPartCylinder& rhs);

    virtual
    ~ConvexPartCylinder(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

    virtual BBox
    get_bounding_box();

protected:
    double y0;          // bottom y value
    double y1;          // top y value
    double radius;      // radius
    double inv_radius;  // one over the radius

    double phi_min;
    double phi_max;
};

typedef ConvexPartCylinder ConcavePartCylinder;

#endif // CONVEXPARTCYLINDER_H
