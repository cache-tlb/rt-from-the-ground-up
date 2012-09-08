// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "whitted.h"
#include "scene.h"
#include "shaderec.h"
#include "material.h"

// ------ default constructor
Whitted::Whitted(void)
    : Tracer()
{}

// ------ constructor
Whitted::Whitted(Scene* _scenePtr)
    : Tracer(_scenePtr)
{}

// ------ destructor
Whitted::~Whitted(void) {}

// ------ trace_ray
RGBColor
Whitted::trace_ray(const Ray ray, const int depth) const {
    if (depth > scene_ptr->vp.max_depth){
        return black;
    }
    else {
        ShadeRec sr(scene_ptr->hit_objects(ray));

        if (sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;
            return (sr.material_ptr->shade(sr));
        }
        else{
            return (scene_ptr->background_color);
        }
    }
}

RGBColor
Whitted::trace_ray(const Ray ray, double &tmin, const int depth) const {
    if (depth > scene_ptr->vp.max_depth){
        tmin = kHugeValue;
        return black;
    }
    else {
        ShadeRec sr(scene_ptr->hit_objects(ray));

        if (sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;
            tmin		= sr.t;     // required for colored transparency
            return (sr.material_ptr->shade(sr));
        }
        else{
            tmin = kHugeValue;

            return (scene_ptr->background_color);
        }
    }
}
