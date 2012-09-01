#ifndef RAYCAST_H
#define RAYCAST_H

#include "tracer.h"

class RayCast: public Tracer {
public:
    RayCast(void);
    RayCast(Scene* _scenePtr);

    virtual
    ~RayCast(void);

    virtual RGBColor
    trace_ray(const Ray ray, const int depth) const;
};


#endif // RAYCAST_H
