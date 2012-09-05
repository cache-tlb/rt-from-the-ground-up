#include "rectangularmap.h"

/* by L. B. */

RectangularMap::RectangularMap(){}

RectangularMap::RectangularMap(const RectangularMap& sm) {}

RectangularMap&
RectangularMap::operator= (const RectangularMap& rhs) {
    if (this == &rhs){
        return (*this);
    }

    return (*this);
}

RectangularMap::~RectangularMap (void) {}

RectangularMap*
RectangularMap::clone(void) const {
    return (new RectangularMap(*this));
}

// ------ get_texel_coordinates
void
RectangularMap::get_texel_coordinates(const Point3D& local_hit_point,
                                    const int xres,
                                    const int yres,
                                    int& row,
                                    int& column) const
{
    float u = (local_hit_point.z + 1.0) / 2.0;
    float v = (local_hit_point.x + 1.0) / 2.0;

    column 	= (int) ((xres - 1) * u);   	// column is across
    row 	= (int)  ((yres - 1) * v);    	// row is up
}
