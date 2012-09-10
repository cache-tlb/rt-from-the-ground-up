#ifndef GLOBALTRACE_H
#define GLOBALTRACE_H

#include "tracer.h"

/* by L.B. */
// sampling the light

class GlobalTrace : public Tracer
{
public:
    GlobalTrace(void);
    GlobalTrace(Scene *_scenePtr);

    virtual RGBColor
    trace_ray(const Ray ray, const int depth) const;

    virtual RGBColor
    trace_ray(const Ray ray, double& tmin, const int depth) const;
};

#endif // GLOBALTRACE_H
