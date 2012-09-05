#ifndef RAMPFBMTEXTURE_H
#define RAMPFBMTEXTURE_H

/* by L.B. */

#include "texture.h"
#include "latticenoise.h"
#include "image.h"

class RampFBmTexture: public Texture {
public:
    // constructors etc ...
    RampFBmTexture(void);
    RampFBmTexture(Image *img_ptr);
    RampFBmTexture(const RampFBmTexture& rft);

    RampFBmTexture&
    operator= (const RampFBmTexture& rhs);

    virtual RampFBmTexture*
    clone(void) const;

    virtual
    ~RampFBmTexture(void);

    virtual RGBColor
    get_color(const ShadeRec& sr) const;

    void
    set_perturbation(const float p);

    void
    set_noise(LatticeNoise *n_ptr);

    void
    set_image(Image *img);

private:
    Image*				ramp_ptr;			// this stores the ramp image
    LatticeNoise*  		noise_ptr;			// supplies the value_fbm noise function
    float				perturbation;		// the amount of fbm ("a" in the book)
    int					hres;				// horizontal ramp image resolution
};

inline void
RampFBmTexture::set_noise(LatticeNoise *n_ptr)
{
    noise_ptr = n_ptr;
}

inline void
RampFBmTexture::set_perturbation(const float p)
{
    perturbation = p;
}

inline void
RampFBmTexture::set_image(Image *img)
{
    ramp_ptr = img;
}

#endif // RAMPFBMTEXTURE_H
