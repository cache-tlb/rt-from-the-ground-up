#ifndef THINLENS_H
#define THINLENS_H

// This file contains the declaration of the class ThinLens

#include "point2d.h"
#include "sampler.h"
#include "scene.h"    // we can #include "Scene.h" here
#include "camera.h"

class ThinLens : public Camera
{
public:
    ThinLens();
    ThinLens(const ThinLens& t);

    virtual Camera*
    clone(void) const;

    ThinLens&
    operator= (const ThinLens& rhs);

    virtual
    ~ThinLens(void);

    void
    set_sampler(Sampler *sp);

    Vector3D
    ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;

    virtual void
    render_scene(const Scene& w);

private:
    float lens_radius;
    float d;
    float f;
    float zoom;
    Sampler* sampler_ptr;
};

#endif // THINLENS_H
