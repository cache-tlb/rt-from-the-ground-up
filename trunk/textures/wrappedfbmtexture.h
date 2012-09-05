#ifndef WRAPPEDFBMTEXTURE_H
#define WRAPPEDFBMTEXTURE_H

/* by L.B. */

#include "texture.h"
#include "latticenoise.h"

class WrappedFBmTexture : public Texture
{
public:
    WrappedFBmTexture(void);
    WrappedFBmTexture(LatticeNoise* n_ptr);
    WrappedFBmTexture(const WrappedFBmTexture& wt);

    WrappedFBmTexture&
    operator= (const WrappedFBmTexture& rhs);

    virtual WrappedFBmTexture*
    clone(void) const;

    virtual
    ~WrappedFBmTexture(void);

    virtual RGBColor
    get_color(const ShadeRec &sr) const;

    void
    set_color(const RGBColor &c);

    void
    set_expansion_number(const float number);

    void
    set_min_value(const float f);

    void
    set_max_value(const float f);

protected:
    float expansion_number;
    float min_value, max_value;
    RGBColor color;
    LatticeNoise *noise_ptr;
};

inline void
WrappedFBmTexture::set_color(const RGBColor &c)
{
    color = c;
}

inline void
WrappedFBmTexture::set_expansion_number(const float number)
{
    expansion_number = number;
}

inline void
WrappedFBmTexture::set_max_value(const float f)
{
    max_value = f;
}

inline void
WrappedFBmTexture::set_min_value(const float f)
{
    min_value = f;
}

#endif // WrappedFBmTexture_H
