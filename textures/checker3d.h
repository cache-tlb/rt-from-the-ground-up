#ifndef CHECKER3D_H
#define CHECKER3D_H

/* by L.B. */

#include "texture.h"

class Checker3D : public Texture
{
public:
    Checker3D(void);
    Checker3D(const Checker3D& sc);

    Checker3D&
    operator= (const Checker3D& rhs);

    virtual Checker3D*
    clone(void) const;

    virtual
    ~Checker3D(void);

    virtual RGBColor
    get_color(const ShadeRec& sr) const;

    void
    set_size(const float s);

    void
    set_color1(const RGBColor& c);

    void
    set_color1(const float r, const float g, const float b);

    void
    set_color2(const RGBColor& c);

    void
    set_color2(const float r, const float g, const float b);

protected:
    RGBColor color1;
    RGBColor color2;
    float size;
};

inline void
Checker3D::set_size(const float s) {
    size = s;
}

inline void
Checker3D::set_color1(const RGBColor &c) {
    color1 = c;
}

inline void
Checker3D::set_color1(const float r, const float g, const float b) {
    color1.r = r; color1.g = g; color1.b = b;
}

inline void
Checker3D::set_color2(const RGBColor &c) {
    color2 = c;
}

inline void
Checker3D::set_color2(const float r, const float g, const float b) {
    color2.r = r; color2.g = g; color2.b = b;
}

#endif // CHECKER3D_H
