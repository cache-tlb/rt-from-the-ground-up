#ifndef SOLIDCYLINDER_H
#define SOLIDCYLINDER_H

/* by L.B. */

#include "compound.h"

class SolidCylinder : public Compound
{
public:
    SolidCylinder(void);
    SolidCylinder(const double bottom, const double top, const double radius);
    SolidCylinder(const SolidCylinder& sc);

    virtual SolidCylinder*
    clone(void) const;

    virtual
    ~SolidCylinder();

    SolidCylinder&
    operator =(const SolidCylinder &rhs);

    virtual bool
    hit(const Ray &ray, double &tmin, ShadeRec &s) const;

    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

private:
    BBox bbox;

};

#endif // SOLIDCYLINDER_H
