#include "fbmtexture.h"
#include "constants.h"

/* by L.B. */

FBmTexture::FBmTexture(void)
    : Texture(),
      max_value(1.0),
      min_value(0.0),
      color(black),
      noise_ptr(NULL)
{}

// ------ constructor
FBmTexture::FBmTexture(LatticeNoise* n_ptr)
    : Texture(),
      max_value(1.0),
      min_value(0.0),
      color(black),
      noise_ptr(n_ptr)
{}

// ------ copy constructor
FBmTexture::FBmTexture(const FBmTexture& ft)
    : Texture(ft),
      max_value(ft.max_value),
      min_value(ft.min_value),
      color(ft.color)

{
    if (ft.noise_ptr)
        noise_ptr = ft.noise_ptr->clone();
    else
        noise_ptr = NULL;
}

// ------ assignment operator

FBmTexture&
FBmTexture::operator= (const FBmTexture& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Texture::operator= (rhs);

    max_value = rhs.max_value;
    min_value = rhs.min_value;

    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }

    if (rhs.noise_ptr)
        noise_ptr = rhs.noise_ptr->clone();

    return (*this);
}


// ------ clone
FBmTexture*
FBmTexture::clone(void) const {
    return (new FBmTexture (*this));
}

// ------ destructor
FBmTexture::~FBmTexture (void) {
    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }
}

RGBColor
FBmTexture::get_color(const ShadeRec& sr) const {

    float value = noise_ptr->value_fbm(sr.local_hit_point); // in the range (0, 1)
    value = min_value + (max_value - min_value) * value;	// in the range (min_value, max_value)

    if(value < 0.0 || value > 1.0)
        return RGBColor(1,0,0); //for debug
    else
        return (value * color);
}
