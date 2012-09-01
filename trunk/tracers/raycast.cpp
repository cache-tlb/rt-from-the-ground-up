#include "raycast.h"

#include "scene.h"
#include "shaderec.h"
#include "material.h"
#include <iostream>
using namespace std;
// ------ default constructor
RayCast::RayCast(void)
    : Tracer()
{}

// ------ constructor
RayCast::RayCast(Scene* _scenePtr)
    : Tracer(_scenePtr)
{}

// ------ destructor
RayCast::~RayCast(void) {}


// ------ trace_ray
// this ignores the depth argument

RGBColor
RayCast::trace_ray(const Ray ray, const int depth) const {
    ShadeRec sr(scene_ptr->hit_objects(ray));
    if (sr.hit_an_object) {
        sr.ray = ray;			// used for specular shading
        return (sr.material_ptr->shade(sr));
    }
    else{
        return (scene_ptr->background_color);
    }
}
