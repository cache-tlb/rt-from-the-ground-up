#ifndef CYLINDRICALMAP_H
#define CYLINDRICALMAP_H

#include "constants.h"
#include "mapping.h"

class CylindricalMap: public Mapping {
public:
    CylindricalMap(void);
    CylindricalMap(const CylindricalMap& sm);

    CylindricalMap&
    operator= (const CylindricalMap& rhs);

    virtual CylindricalMap*
    clone(void) const;

    ~CylindricalMap(void);

    virtual void
    get_texel_coordinates(const Point3D& local_hit_point,
                          const int xres,
                          const int yres,
                          int& row,
                          int& column) const;
};

#endif // CYLINDRICALMAP_H
