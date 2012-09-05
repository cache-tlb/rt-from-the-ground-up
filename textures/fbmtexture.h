#ifndef FBMTEXTURE_H
#define FBMTEXTURE_H

#include "texture.h"
#include "latticenoise.h"

/* by L.B. */

class FBmTexture: public Texture {
public:
    // constructors etc ...
    FBmTexture(void);
    FBmTexture(LatticeNoise* n_ptr);
    FBmTexture(const FBmTexture& ft);

    FBmTexture&
    operator= (const FBmTexture& rhs);

    virtual FBmTexture*
    clone(void) const;

    virtual
    ~FBmTexture(void);

    void
    set_min_value(const float v);

    void
    set_max_value(const float v);

    void
    set_color(const RGBColor& c);

    void
    set_noise(LatticeNoise *noise);

    virtual RGBColor
    get_color(const ShadeRec& sr) const;

private:
    LatticeNoise*		noise_ptr;
    RGBColor 	  		color;
    float		  		min_value, max_value;	// scaling factors
};

inline void
FBmTexture::set_color(const RGBColor &c)
{
    color = c;
}

inline void
FBmTexture::set_max_value(const float v)
{
    max_value = v;
}

inline void
FBmTexture::set_min_value(const float v)
{
    min_value = v;
}

inline void
FBmTexture::set_noise(LatticeNoise *noise)
{
    noise_ptr = noise;
}

#endif // FBMTEXTURE_H
