#include "wrappedfbmtexture.h"
#include "constants.h"

/* by L.B. */

WrappedFBmTexture::WrappedFBmTexture(void)
    : Texture(),
      expansion_number(1.0),
      min_value(0.0),
      max_value(1.0),
      color(black),
      noise_ptr(NULL)
{}

// ------ constructor
WrappedFBmTexture::WrappedFBmTexture(LatticeNoise* n_ptr)
    : Texture(),
      expansion_number(1.0),
      min_value(0.0),
      max_value(1.0),
      color(black),
      noise_ptr(n_ptr)
{}

// ------ copy constructor
WrappedFBmTexture::WrappedFBmTexture(const WrappedFBmTexture& wt)
    : Texture(wt),
      expansion_number(wt.expansion_number),
      min_value(wt.min_value),
      max_value(wt.max_value),
      color(wt.color)

{
    if (wt.noise_ptr)
        noise_ptr = wt.noise_ptr->clone();
    else
        noise_ptr = NULL;
}

// ------ assignment operator

WrappedFBmTexture&
WrappedFBmTexture::operator= (const WrappedFBmTexture& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Texture::operator= (rhs);

    expansion_number = rhs.expansion_number;
    min_value = rhs.min_value;
    max_value = rhs.max_value;

    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }

    if (rhs.noise_ptr)
        noise_ptr = rhs.noise_ptr->clone();

    return (*this);
}


// ------ clone
WrappedFBmTexture*
WrappedFBmTexture::clone(void) const {
    return (new WrappedFBmTexture (*this));
}

// ------ destructor
WrappedFBmTexture::~WrappedFBmTexture (void) {
    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }
}

RGBColor
WrappedFBmTexture::get_color(const ShadeRec& sr) const {

    float noise = expansion_number * noise_ptr ->value_fbm(sr.local_hit_point);
    float value = noise - floor(noise);
    value = min_value + (max_value - min_value) * value;

    return (value * color);
}
