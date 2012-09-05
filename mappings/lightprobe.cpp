#include "lightprobe.h"

/* by L.B. */

LightProbe::LightProbe(void)
    : map_type(light_probe)
{}

LightProbe::LightProbe(const LightProbe& sm)
    : map_type(sm.map_type)
{}

LightProbe&
LightProbe::operator= (const LightProbe& rhs) {
    if (this == &rhs){
        return (*this);
    }

    map_type = rhs.map_type;

    return (*this);
}

LightProbe::~LightProbe (void) {}

LightProbe*
LightProbe::clone(void) const {
    return (new LightProbe(*this));
}

// ------ get_texel_coordinates
void
LightProbe::get_texel_coordinates(const Point3D& local_hit_point,
                                    const int xres,
                                    const int yres,
                                    int& row,
                                    int& column) const
{

    float x = local_hit_point.x;
        float y = local_hit_point.y;
        float z = local_hit_point.z;

        float d = sqrt(x * x + y * y);
        float sin_beta = y / d;
        float cos_beta = x / d;
        float alpha;

        if (map_type == light_probe)   // the default
            alpha = acos(z);

        if (map_type == panoramic)
            alpha = acos(-z);

        float r = alpha * invPI;
        float u = (1.0 + r * cos_beta) * 0.5;
        float v = (1.0 + r * sin_beta) * 0.5;
        column 	= (int) ((xres - 1) * u);
        row 	= (int) ((yres - 1) * v);

}
