#ifndef AREALIGHT_H
#define AREALIGHT_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "rgbcolor.h"
#include "vector3d.h"
#include "point3d.h"
#include "normal.h"
#include "light.h"
#include "material.h"
#include "shape.h"

class AreaLight: public Light {
public:
    AreaLight(void);
    AreaLight(const AreaLight& al);

    virtual AreaLight*
    clone(void) const;

    virtual
    ~AreaLight(void);

    AreaLight&
    operator= (const AreaLight& rhs);

    void
    set_object(Shape* obj_ptr);

    virtual Vector3D
    get_direction(ShadeRec& s);

    virtual RGBColor
    L(ShadeRec& sr);

    virtual bool
    in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual float
    G(const ShadeRec& sr) const;

    virtual float
    pdf(const ShadeRec& sr) const;

private:
    Shape*      object_ptr;
    Material*   material_ptr;	 // will be an emissive material (must be?)
    Point3D     sample_point;
    Normal      light_normal;    // assigned in get_direction - which therefore can't be const for any light
    Vector3D    wi;			     // unit direction from hit point being shaded to sample point on light surface
};

// ------ set_object
inline void
AreaLight::set_object(Shape* obj_ptr) {
    object_ptr = obj_ptr;
    material_ptr = object_ptr->get_material()->clone();
}

#endif // AREALIGHT_H
