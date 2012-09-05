#ifndef TINSTANCE_H
#define TINSTANCE_H

/* by L.B. */

#include "texture.h"

class TInstance: public Texture {
public:
    // constructors etc
    TInstance(void);
    TInstance(Texture *t_ptr);
    TInstance(const TInstance& sc);

    TInstance&
    operator= (const TInstance& rhs);

    virtual TInstance*
    clone(void) const;

    virtual
    ~TInstance(void);

    void
    set_texture(Texture* t_ptr);

    virtual RGBColor
    get_color(const ShadeRec& sr) const;

    // affine tranformation functions:
    void
    translate(const Vector3D& trans);

    void
    translate(const double dx, const double dy, const double dz);

    void
    scale(const Vector3D& s);

    void
    scale(const double sx, const double sy, const double sz);

    virtual void
    rotate_x(const double theta);

    virtual void
    rotate_y(const double theta);

    virtual void
    rotate_z(const double theta);

    void
    shear(const Matrix& s);

private:
    Texture* texture_ptr;	// texture being transformed
    Matrix inv_matrix;		// inverse transformation matrix
};

#endif // TINSTANCE_H
