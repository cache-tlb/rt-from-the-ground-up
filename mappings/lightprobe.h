#ifndef LIGHTPROBE_H
#define LIGHTPROBE_H

#include "constants.h"
#include "mapping.h"

/* by L.B. */
typedef enum {
    light_probe,
    panoramic
} MapType;

class LightProbe: public Mapping {
public:
    LightProbe(void);
    LightProbe(const LightProbe& sm);

    LightProbe&
    operator= (const LightProbe& rhs);

    virtual LightProbe*
    clone(void) const;

    ~LightProbe(void);

    virtual void
    get_texel_coordinates(const Point3D& local_hit_point,
                          const int xres,
                          const int yres,
                          int& row,
                          int& column) const;
    MapType map_type;
};

#endif // LIGHTPROBE_H
