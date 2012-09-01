#ifndef MATERIAL_H
#define MATERIAL_H

#include "scene.h"			// required for the shade function in all derived classes
#include "rgbcolor.h"
#include "shaderec.h"

class Material {
public:
    Material(void);
    Material(const Material& material);

    virtual Material*
    clone(void) const = 0;

    virtual
    ~Material(void);

    virtual RGBColor
    shade(ShadeRec& sr);

    virtual RGBColor
    get_Le(ShadeRec& sr) const;

    virtual RGBColor
    area_light_shade(ShadeRec& sr);

protected:
    Material&
    operator= (const Material& rhs);
};


#endif // MATERIAL_H
