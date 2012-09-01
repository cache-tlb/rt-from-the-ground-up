#ifndef PINHOLE_H
#define PINHOLE_H

// This file contains the declaration of the class Pinhole

#include "point2d.h"
#include "scene.h"    // we can #include "Scene.h" here
#include "camera.h"

// ------ class Pinhole
class Pinhole: public Camera {
public:
    Pinhole();
    Pinhole(const Pinhole& ph);

    virtual Camera*
    clone(void) const;

    Pinhole&
    operator= (const Pinhole& rhs);

    virtual
    ~Pinhole();

    void
    set_view_distance(const float vpd);

    void
    set_zoom(const float zoom_factor);

    Vector3D
    get_direction(const Point2D& p) const;

    virtual void
    render_scene(const Scene& w);

private:
    float	d;		// view plane distance
    float	zoom;	// zoom factor
};


// ------ set_vpd
inline void
Pinhole::set_view_distance(float _d) {
    d = _d;
}

// ------ set_zoom
inline void
Pinhole::set_zoom(float zoom_factor) {
    zoom = zoom_factor;
}

#endif // PINHOLE_H
