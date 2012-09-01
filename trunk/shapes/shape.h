#ifndef SHAPE_H
#define SHAPE_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <math.h>  // a lot of hit functions use use maths functions

#include "constants.h"
#include "bbox.h"
#include "rgbcolor.h"
#include "point3d.h"
#include "vector3d.h"
#include "normal.h"
#include "ray.h"
#include "shaderec.h"

class Material;

// ------ class Shape

class Shape {
public:
    Shape(void);
    Shape(const Shape& object);

    virtual Shape*
    clone(void) const = 0;

    virtual
    ~Shape(void);

    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

    virtual void 							// This needs to be virtual so that it can be overridden in Compound
    set_material(Material* mPtr); 			// It therefore shouldn't be inlined

    Material*
    get_material(void) const;

    // The following three functions are only required for Chapter 3

    /*void
    set_color(const RGBColor& c);

    void
    set_color(const float r, const float g, const float b);

    RGBColor
    get_color(void);
    */

    virtual void
    set_bounding_box(void);

    virtual BBox
    get_bounding_box(void);

    virtual void 										// required for compound objects
    add_object(Shape* object_ptr);

    // The following two functions are only required for objects that are light sources, eg disks, rectangles, and spheres

    virtual Point3D
    sample(void);

    virtual float
    pdf(const ShadeRec& sr);

    // The following two functions allow us to simplify the code for smooth shaded triangle meshes

    virtual Normal
    get_normal(void) const;

    virtual Normal
    get_normal(const Point3D& p);

    /* not sure */
    virtual bool
    shadow_hit(const Ray& ray, float& tmin) const;

protected:
    mutable Material*   material_ptr;   	// mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
    //RGBColor   			color;				// only used for Bare Bones ray tracing

    bool shadows;
    Shape&
    operator= (const Shape& rhs);
};

/*
// ------  set_color
inline void
Shape::set_color(const RGBColor& c) {
    color = c;
}

// ------  set_color
inline void
Shape::set_color(const float r, const float g, const float b) {
    color.r = r;
    color.b = b;
    color.g = g;
}

// ------  get_color
inline RGBColor
Shape::get_color(void) {
    return (color);
}
*/

#endif // SHAPE_H
