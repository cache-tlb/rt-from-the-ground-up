#include "cylindricalmap.h"

/* by L.B. */
CylindricalMap::CylindricalMap(void) {}

CylindricalMap::CylindricalMap(const CylindricalMap& sm) {}

CylindricalMap&
CylindricalMap::operator= (const CylindricalMap& rhs) {
    if (this == &rhs){
        return (*this);
    }

    return (*this);
}

CylindricalMap::~CylindricalMap (void) {}

CylindricalMap*
CylindricalMap::clone(void) const {
    return (new CylindricalMap(*this));
}

// ------ get_texel_coordinates
void
CylindricalMap::get_texel_coordinates(const Point3D& local_hit_point,
                                    const int xres,
                                    const int yres,
                                    int& row,
                                    int& column) const
{

    float phi   = atan2(local_hit_point.x, local_hit_point.z);
    if (phi < 0.0){
        phi += TWO_PI;
    }

    float u = phi * invTWO_PI;
    float v = (local_hit_point.y + 1.0) / 2.0;

    column 	= (int) ((xres - 1) * u);   	// column is across
    row 	= (int)  ((yres - 1) * v);    	// row is up
}
