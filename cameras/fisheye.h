#ifndef FISHEYE_H
#define FISHEYE_H

#include "camera.h"
#include "scene.h"

class Fisheye : public Camera
{
public:
    Fisheye();
    Fisheye(const Fisheye& f);

    virtual Camera*
    clone(void) const;

    Fisheye&
    operator= (const Fisheye& rhs);

    virtual
    ~Fisheye(void);

    Vector3D
    ray_direction(const Point2D& pp, const int hres,
                  const int vres, const float s, float& r_squared)const;

    void
    set_fov(const float fov);

    virtual void
    render_scene(const Scene &w);

private:
    float psi_max;
};

inline void
Fisheye::set_fov(const float fov)
{
    psi_max = fov / 2.0;
}

#endif // FISHEYE_H
