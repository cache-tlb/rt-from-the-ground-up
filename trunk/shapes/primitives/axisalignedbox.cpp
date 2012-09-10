#include "axisalignedbox.h"
#include "maths.h"

AxisAlignedBox::AxisAlignedBox(void)
    : x0(0),x1(1),
      y0(0),y1(1),
      z0(0),z1(1)
{}

AxisAlignedBox::AxisAlignedBox(const Vector3D &p1, const Vector3D &p2)
    : x0(min(p1.x,p2.x)), x1(max(p1.x,p2.x)),
      y0(min(p1.y,p2.y)), y1(max(p1.y,p2.y)),
      z0(min(p1.z,p2.z)), z1(max(p1.z,p2.z))
{}

AxisAlignedBox::AxisAlignedBox(const AxisAlignedBox &a)
    : x0(a.x0), x1(a.x1),
      y0(a.y0), y1(a.y1),
      z0(a.z0), z1(a.z1)
{}

AxisAlignedBox*
AxisAlignedBox::clone(void) const
{
    return (new AxisAlignedBox(*this));
}

// ------ assignment operator
AxisAlignedBox&
AxisAlignedBox::operator= (const AxisAlignedBox& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Shape::operator= (rhs);

    x0 = rhs.x0; x1 = rhs.x1;
    y0 = rhs.y0; y1 = rhs.y1;
    z0 = rhs.z0; z1 = rhs.z1;

    return (*this) ;
}

AxisAlignedBox::~AxisAlignedBox() {}

BBox
AxisAlignedBox::get_bounding_box(void) {
    return BBox(x0,x1,y0,y1,z0,z1);
}

bool
AxisAlignedBox::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
    double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    double t0, t1;

    // find largest entering t value

    if (tx_min > ty_min){
        t0 = tx_min;
    }
    else{
        t0 = ty_min;
    }

    if (tz_min > t0){
        t0 = tz_min;
    }

    // find smallest exiting t value

    if (tx_max < ty_max){
        t1 = tx_max;
    }
    else{
        t1 = ty_max;
    }

    if (tz_max < t1){
        t1 = tz_max;
    }

    // t0 is max(tx_min,ty_min,tz_min)
    // t1 is min(tx_max,ty_max,tz_max)
    // normal is all point opposite ray.d

    if(t0 < t1 && t1 > kEpsilon) {
        if(t0 > kEpsilon){
            // ray.o is outside the box
            tmin = t0;
            if(t0 == tx_min){
                if(dx < 0)
                    sr.normal = Normal(1,0,0);
                else
                    sr.normal = Normal(-1,0,0);
            }
            else if(t0 == ty_min){
                if(dy < 0)
                    sr.normal = Normal(0,1,0);
                else
                    sr.normal = Normal(0,-1,0);
            }
            else{
                if(dz < 0)
                    sr.normal = Normal(0,0,1);
                else
                    sr.normal = Normal(0,0,-1);
            }
        }
        else{
            // ray.o is inside the box
            tmin = t1;
            if(t1 == tx_max){
                if(dx < 0)
                    sr.normal = Normal(-1,0,0);
                else
                    sr.normal = Normal(1,0,0);
            }
            else if(t1 == ty_max){
                if(dy < 0)
                    sr.normal = Normal(0,-1,0);
                else
                    sr.normal = Normal(0,1,0);
            }
            else{
                if(dz < 0)
                    sr.normal = Normal(0,0,-1);
                else
                    sr.normal = Normal(0,0,1);
            }
        }
        sr.local_hit_point = ray.o + tmin * ray.d;
        return true;
    }
    else{
        return false;
    }
}

bool
AxisAlignedBox::shadow_hit(const Ray &ray, float &tmin) const
{
    double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
    double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    double t0, t1;

    // find largest entering t value

    if (tx_min > ty_min){
        t0 = tx_min;
    }
    else{
        t0 = ty_min;
    }

    if (tz_min > t0){
        t0 = tz_min;
    }

    // find smallest exiting t value

    if (tx_max < ty_max){
        t1 = tx_max;
    }
    else{
        t1 = ty_max;
    }

    if (tz_max < t1){
        t1 = tz_max;
    }

    // t0 is max(tx_min,ty_min,tz_min)
    // t1 is min(tx_max,ty_max,tz_max)

    if(t0 < t1 && t1 > kEpsilon) {
        if(t0 > kEpsilon){  // ray.o is outside the box
            tmin = t0;
        }
        else{               // ray.o is inside the box
            tmin = t1;
        }
        return true;
    }
    else{
        return false;
    }
}
