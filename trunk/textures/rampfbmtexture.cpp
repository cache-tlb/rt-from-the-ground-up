#include "rampfbmtexture.h"

RampFBmTexture::RampFBmTexture(void)
    : Texture(),
      ramp_ptr(NULL),
      noise_ptr(NULL),
      perturbation(1.0),
      hres(1)
{}

// ------ constructor
RampFBmTexture::RampFBmTexture(Image* img_ptr)
    : Texture(),
      ramp_ptr(img_ptr),
      noise_ptr(NULL),
      perturbation(1.0),
      hres(img_ptr->get_hres())
{}

// ------ copy constructor
RampFBmTexture::RampFBmTexture(const RampFBmTexture& rft)
    : Texture(rft),
      perturbation(rft.perturbation),
      hres(rft.hres)

{
    if (rft.noise_ptr)
        noise_ptr = rft.noise_ptr->clone();
    else
        noise_ptr = NULL;

    if(rft.ramp_ptr)
        ramp_ptr = rft.ramp_ptr;
    else
        ramp_ptr = NULL;
}

// ------ assignment operator

RampFBmTexture&
RampFBmTexture::operator= (const RampFBmTexture& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Texture::operator= (rhs);

    perturbation = rhs.perturbation;

    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }

    if (rhs.noise_ptr)
        noise_ptr = rhs.noise_ptr->clone();

    if (rhs.ramp_ptr)
        ramp_ptr = rhs.ramp_ptr;
    else
        ramp_ptr = NULL;

    return (*this);
}


// ------ clone
RampFBmTexture*
RampFBmTexture::clone(void) const {
    return (new RampFBmTexture (*this));
}

// ------ destructor
RampFBmTexture::~RampFBmTexture (void) {
    if (noise_ptr) {
        delete noise_ptr;
        noise_ptr = NULL;
    }
}


RGBColor
RampFBmTexture::get_color(const ShadeRec& sr) const {

    float 	noise 	= noise_ptr->value_fbm(sr.local_hit_point);
    float 	y 		= sr.local_hit_point.y + perturbation * noise;
    float 	u 		= (1.0 + sin(y)) / 2.0;
    int 	row 	= 0;    // use top row of ramp image
    int 	column 	= (int) (u * (hres - 1));

    return (ramp_ptr->get_color(row, column));
}
