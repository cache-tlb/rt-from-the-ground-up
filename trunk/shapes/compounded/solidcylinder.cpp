#include "solidcylinder.h"
#include "primitives/opencylinder.h"
#include "primitives/disk.h"

SolidCylinder::SolidCylinder(const double bottom, const double top, const double radius)
    : Compound()
{
    objects.push_back(new Disk(	Point3D(0, bottom, 0),  // bottom
                                Normal(0, -1, 0),
                                radius));

    objects.push_back(new Disk(	Point3D(0, top, 0),     // top
                                Normal(0, 1, 0),
                                radius));

    OpenCylinder *open = new OpenCylinder(bottom, top, radius);
    objects.push_back(open);                            // wall
    bbox = open->get_bounding_box();
}

SolidCylinder::SolidCylinder(void)
    : Compound()
{
    objects.push_back(new Disk(	Point3D(0, 0, 0), 			// bottom
                                Normal(0, -1, 0),
                                1));

    objects.push_back(new Disk(	Point3D(0, 1, 0), 			// top
                                Normal(0, 1, 0),
                                1));

    OpenCylinder *open = new OpenCylinder(0, 1, 1);
    objects.push_back(open);                            // wall
    bbox = open->get_bounding_box();
}

SolidCylinder::SolidCylinder(const SolidCylinder &sc)
    : Compound(sc),
      bbox(sc.bbox)
{}

SolidCylinder::~SolidCylinder() {}

SolidCylinder&
SolidCylinder::operator =(const SolidCylinder& rhs)
{
    if(&rhs == this){
        return (*this);
    }

    Compound::operator =(rhs);

    bbox = rhs.bbox;

    return (*this);
}

SolidCylinder*
SolidCylinder::clone(void) const
{
    return (new SolidCylinder(*this));
}

bool
SolidCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (bbox.hit(ray))
        return (Compound::hit(ray, tmin, sr));
    else
        return (false);
}

bool
SolidCylinder::shadow_hit(const Ray &ray, float &tmin) const {
    if(bbox.hit(ray))
        return (Compound::shadow_hit(ray, tmin));
    else
        return false;
}
