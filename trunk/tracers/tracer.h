#ifndef TRACER_H
#define TRACER_H

#include "constants.h"
#include "ray.h"
#include "rgbcolor.h"

class Scene;

class Tracer {
public:
    Tracer(void);
    Tracer(Scene* _scene_ptr);

    virtual
    ~Tracer(void);

    virtual RGBColor
    trace_ray(const Ray ray, double &tmin, const int depth) const;

    virtual RGBColor
    trace_ray(const Ray ray, const int depth) const;

protected:
    Scene* scene_ptr;
};

#endif // TRACER_H
