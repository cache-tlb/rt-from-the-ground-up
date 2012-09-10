#ifndef DISK_H
#define DISK_H

#include "shape.h"

// ------ class disk
/* by L.B. */

class Disk : public Shape
{
public:
    Disk(void);   												// default constructor
    Disk(const Point3D& point, const Normal& normal, const float radius);	// constructor
    Disk(const Disk& disk); 									// copy constructor

    virtual Disk* 												// virtual copy constructor
    clone(void) const;

    Disk& 														// assignment operator
    operator= (const Disk& rhs);

    virtual														// destructor
    ~Disk(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

private:
    Point3D center;
    Normal normal;
    float r_squared;
};

#endif // DISK_H
