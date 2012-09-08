#include "tracer.h"

// ------ default constructor
Tracer::Tracer(void)
    : scene_ptr(NULL)
{}

// ------ constructor
Tracer::Tracer(Scene* _scenePtr)
    : scene_ptr(_scenePtr)
{}

// ------ destructor
Tracer::~Tracer(void) {
    if (scene_ptr){
        scene_ptr = NULL;
    }
}

// ------ trace_ray
RGBColor
Tracer::trace_ray(const Ray ray, double &tmin, const int depth) const {
    return (black);
}

// ------ trace_ray
RGBColor
Tracer::trace_ray(const Ray ray, const int depth) const {
    return (black);
}
