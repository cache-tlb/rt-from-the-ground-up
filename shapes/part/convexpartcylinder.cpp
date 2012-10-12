/* by L.B. */

#include "convexpartcylinder.h"

ConvexPartCylinder::ConvexPartCylinder(void)
    : Shape(),
      y0(-1.0),
      y1(1.0),
      radius(1.0),
      inv_radius(1.0),
      phi_min(0.0),
      phi_max(180.0)
{}

// ------ constructor
ConvexPartCylinder::ConvexPartCylinder(const double bottom, const double top, const double r,
                                       double phi1, double phi2)
    : Shape(),
      y0(bottom),
      y1(top),
      radius(r),
      inv_radius(1.0 / r),
      phi_min(phi1),
      phi_max(phi2)
{}

// ------ copy constructor
ConvexPartCylinder::ConvexPartCylinder(const ConvexPartCylinder& c)
    : Shape(c),
      y0(c.y0),
      y1(c.y1),
      radius(c.radius),
      inv_radius(c.inv_radius),
      phi_min(c.phi_min),
      phi_max(c.phi_max)
{}

// ------ clone
ConvexPartCylinder*
ConvexPartCylinder::clone(void) const {
    return (new ConvexPartCylinder (*this));
}

// ------ assignment operator
ConvexPartCylinder&
ConvexPartCylinder::operator= (const ConvexPartCylinder& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Shape::operator= (rhs);

    y0          = rhs.y0;
    y1          = rhs.y1;
    radius      = rhs.radius;
    inv_radius  = rhs.inv_radius;
    phi_min     = rhs.phi_min;
    phi_max     = rhs.phi_max;

    return (*this) ;
}

ConvexPartCylinder::~ConvexPartCylinder(void) {}

BBox
ConvexPartCylinder::get_bounding_box() {
    Point3D p1(-radius, y0, -radius), p2(radius, y1, radius);
    return BBox(p1,p2);
}


bool
ConvexPartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

    double t;
    double ox = ray.o.x;
    double oy = ray.o.y;
    double oz = ray.o.z;
    double dx = ray.d.x;
    double dy = ray.d.y;
    double dz = ray.d.z;

    double a = dx * dx + dz * dz;
    double b = 2.0 * (ox * dx + oz * dz);
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c ;


    if (disc < 0.0){
        return(false);
    }
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        for(int ii = 0; ii < 2; ii++){
            if (t > kEpsilon) {

                double yhit = oy + t * dy;

                if (yhit > y0 && yhit < y1) {
                    double xhit = ox + t * dx, zhit = oz + t * dz;
                    sr.normal = Normal(xhit * inv_radius, 0.0, zhit * inv_radius);

                    double phi = atan2(xhit, zhit);
                    if (phi < 0.0)
                        phi += TWO_PI;

                    if (phi >= phi_min*PI_ON_180 && phi <= phi_max*PI_ON_180) {
                        tmin = t;
                        if (-ray.d * sr.normal < 0.0){
                            sr.normal = -sr.normal;
                        }

                        sr.local_hit_point = ray.o + tmin * ray.d;

                        return (true);
                    }

                }
            }

            t = (-b + e) / denom;    // larger root
        }
    }

    return (false);
}

// ------ shadow_hit
bool
ConvexPartCylinder::shadow_hit(const Ray &ray, float &tmin) const {

    double t;
    double ox = ray.o.x;
    double oy = ray.o.y;
    double oz = ray.o.z;
    double dx = ray.d.x;
    double dy = ray.d.y;
    double dz = ray.d.z;

    double a = dx * dx + dz * dz;
    double b = 2.0 * (ox * dx + oz * dz);
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c ;


    if (disc < 0.0){
        return(false);
    }
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        for(int ii = 0; ii < 2; ii++){
            if (t > kEpsilon) {

                double yhit = oy + t * dy;

                if (yhit > y0 && yhit < y1) {
                    double xhit = ox + t * dx, zhit = oz + t * dz;

                    double phi = atan2(xhit, zhit);
                    if (phi < 0.0)
                        phi += TWO_PI;

                    if (phi >= phi_min && phi <= phi_max) {
                        tmin = t;

                        return (true);
                    }

                }
            }

            t = (-b + e) / denom;    // larger root
        }
    }

    return (false);
}
