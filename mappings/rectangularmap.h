#ifndef RECTANGULARMAP_H
#define RECTANGULARMAP_H

/* by L.B. */
#include "constants.h"
#include "mapping.h"

class RectangularMap : public Mapping {
public:
    RectangularMap();
    RectangularMap(const RectangularMap& sm);

    RectangularMap&
    operator= (const RectangularMap& rhs);

    virtual RectangularMap*
    clone(void) const;

    ~RectangularMap(void);

    virtual void
    get_texel_coordinates(const Point3D& local_hit_point,
                          const int xres,
                          const int yres,
                          int& row,
                          int& column) const;
};

typedef RectangularMap SquareMap;

#endif // RECTANGULARMAP_H
