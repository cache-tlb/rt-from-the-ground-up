#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

/*
  This file contains the declaration of the class Orthographic
  Warning: the class only suppot z-axis aligned orthographic projection
  */
#include "camera.h"
#include "scene.h"

class Orthographic : public Camera
{
public:
    Orthographic();
    Orthographic(const Orthographic& oh);

    virtual Camera*
    clone(void) const;

    Orthographic&
    operator= (const Orthographic& rhs);

    virtual
    ~Orthographic(void);

    virtual void
    render_scene(const Scene &w);

};

#endif // ORTHOGRAPHIC_H
