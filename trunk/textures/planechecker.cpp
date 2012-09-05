/* by L.B. */
#include "constants.h"
#include "planechecker.h"

PlaneChecker::PlaneChecker(void)
    :	Texture(),
        line_width(0.0),
        size(1.0),
        color1(white),
        color2(0.5),
        line_color(black)
{}

PlaneChecker::PlaneChecker(const PlaneChecker& sc)
    : 	Texture(sc),
        line_width(sc.line_width),
        size(sc.size),
        color1(sc.color1),
        color2(sc.color2),
        line_color(sc.line_color)
{}

PlaneChecker&
PlaneChecker::operator= (const PlaneChecker& rhs)
{
    if (this == &rhs){
        return (*this);
    }

    Texture::operator=(rhs);

    line_width  = rhs.line_width;
    size        = rhs.size;
    color1      = rhs.color1;
    color2      = rhs.color2;
    line_color  = rhs.line_color;

    return (*this);
}

PlaneChecker*
PlaneChecker::clone(void) const {
    return (new PlaneChecker(*this));
}

PlaneChecker::~PlaneChecker(void) {}

RGBColor
PlaneChecker::get_color(const ShadeRec& sr) const {
    float x = sr.local_hit_point.x;
    float z = sr.local_hit_point.z;
    int ix = floor(x / size);
    int iz = floor(z / size);
    float fx = x / size - ix;
    float fz = z / size - iz;
    float width = 0.5 * line_width / size;
    bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

    if ((ix + iz) % 2 == 0) {
        if (!in_outline)
            return (color1);
    }
    else {
        if (!in_outline)
            return (color2);
    }

    return (line_color);
}
