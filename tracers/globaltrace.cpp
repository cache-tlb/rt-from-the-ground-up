/* by L.B.*/

#include "globaltrace.h"
#include "scene.h"
#include "shaderec.h"
#include "material.h"

// ------ default constructor
GlobalTrace::GlobalTrace(void)
    : Tracer()
{}

// ------ default constructor
GlobalTrace::GlobalTrace(Scene* _scenePtr)
    : Tracer(_scenePtr)
{}

// ------ trace_ray
RGBColor
GlobalTrace::trace_ray(const Ray ray, const int depth) const {
    if (depth > scene_ptr->vp.max_depth)
        return (black);
    else {
        ShadeRec sr(scene_ptr->hit_objects(ray));

        if (sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;

            return (sr.material_ptr->global_shade(sr));
        }
        else
            return (scene_ptr->background_color);
    }
}

// ------ trace_ray
// this version has tmin as an argument, and is used only with the Dielectric material
// for color filtering
RGBColor
GlobalTrace::trace_ray(const Ray ray, double& tmin, const int depth) const {
    if (depth > scene_ptr->vp.max_depth){
        tmin = kHugeValue;  // modified by L.B.
        return (black);
    }
    else {
        ShadeRec sr(scene_ptr->hit_objects(ray));

        if (sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;
            tmin = sr.t;     // required for colored transparency
            return (sr.material_ptr->global_shade(sr));
        }
        else{
            tmin = kHugeValue;
            return (scene_ptr->background_color);
        }
    }
}
