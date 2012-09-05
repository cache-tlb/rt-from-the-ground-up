/* by L.B. */

#include "tinstance.h"
#include "constants.h"

TInstance::TInstance(void)
    : Texture(),
      inv_matrix(),
      texture_ptr(NULL)
{}

TInstance::TInstance(Texture* t_ptr)
    : Texture(),
      inv_matrix(),
      texture_ptr(t_ptr)
{}

TInstance::TInstance(const TInstance& it)
    : Texture(it),
      inv_matrix(it.inv_matrix)
{
    if (it.texture_ptr)
        texture_ptr = it.texture_ptr->clone();
    else
        texture_ptr = NULL;
}

TInstance&
TInstance::operator= (const TInstance& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Texture::operator= (rhs);

    if (texture_ptr) {
        delete texture_ptr;
        texture_ptr = NULL;
    }

    if (rhs.texture_ptr)
        texture_ptr = rhs.texture_ptr->clone();

    return (*this);
}

TInstance*
TInstance::clone(void) const {
    return (new TInstance (*this));
}

TInstance::~TInstance (void) {
    if (texture_ptr) {
        delete texture_ptr;
        texture_ptr = NULL;
    }
}

//-----------------------------------------
void
TInstance::set_texture(Texture *t_ptr)
{
    texture_ptr = t_ptr;
}

RGBColor
TInstance::get_color(const ShadeRec& sr) const
{
    ShadeRec local_sr(sr);
    local_sr.local_hit_point = inv_matrix * local_sr.local_hit_point;

    return (texture_ptr->get_color(local_sr));
}

void
TInstance::translate(const Vector3D &trans)
{
    translate(trans.x,trans.y,trans.z);
}

void
TInstance::translate(const double dx, const double dy, const double dz)
{
    Matrix inv_translation_matrix;				// temporary inverse translation matrix

    inv_translation_matrix.m[0][3] = -dx;
    inv_translation_matrix.m[1][3] = -dy;
    inv_translation_matrix.m[2][3] = -dz;

    inv_matrix = inv_matrix * inv_translation_matrix;
}

void
TInstance::scale(const Vector3D &s) {
    scale(s.x,s.y,s.z);
}

void
TInstance::scale(const double sx, const double sy, const double sz) {

    Matrix inv_scaling_matrix;			// temporary inverse scaling matrix

    inv_scaling_matrix.m[0][0] = 1.0 / sx;
    inv_scaling_matrix.m[1][1] = 1.0 / sy;
    inv_scaling_matrix.m[2][2] = 1.0 / sz;

    inv_matrix = inv_matrix * inv_scaling_matrix;
}

void
TInstance::rotate_x(const double theta)
{
    double sin_theta = sin(theta * PI_ON_180);
    double cos_theta = cos(theta * PI_ON_180);

    Matrix inv_x_rotation_matrix;	// temporary inverse rotation matrix about x axis

    inv_x_rotation_matrix.m[1][1] = cos_theta;
    inv_x_rotation_matrix.m[1][2] = sin_theta;
    inv_x_rotation_matrix.m[2][1] = -sin_theta;
    inv_x_rotation_matrix.m[2][2] = cos_theta;

    inv_matrix = inv_matrix * inv_x_rotation_matrix;
}

void
TInstance::rotate_y(const double theta)
{
    double sin_theta = sin(theta * PI / 180.0);
    double cos_theta = cos(theta * PI / 180.0);

    Matrix inv_y_rotation_matrix;					// temporary inverse rotation matrix about y axis

    inv_y_rotation_matrix.m[0][0] = cos_theta;
    inv_y_rotation_matrix.m[0][2] = -sin_theta;
    inv_y_rotation_matrix.m[2][0] = sin_theta;
    inv_y_rotation_matrix.m[2][2] = cos_theta;

    inv_matrix = inv_matrix * inv_y_rotation_matrix;
}

void
TInstance::rotate_z(const double theta)
{
    double sin_theta = sin(theta * PI / 180.0);
    double cos_theta = cos(theta * PI / 180.0);

    Matrix inv_z_rotation_matrix;					// temporary inverse rotation matrix about y axis

    inv_z_rotation_matrix.m[0][0] = cos_theta;
    inv_z_rotation_matrix.m[0][1] = sin_theta;
    inv_z_rotation_matrix.m[1][0] = -sin_theta;
    inv_z_rotation_matrix.m[1][1] = cos_theta;

    inv_matrix = inv_matrix * inv_z_rotation_matrix;
}

void
TInstance::shear(const Matrix &s)
{
    Matrix inverse_shearing_matrix;    // inverse shear matrix

    // discriminant

    double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
                    + s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

    // diagonals

    inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
    inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
    inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
    inverse_shearing_matrix.m[3][3] = d;

    // first row

    inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
    inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

    // second row

    inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
    inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

    // third row

    inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
    inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;

    // divide by discriminant

    inverse_shearing_matrix = inverse_shearing_matrix / d;

    inv_matrix = inv_matrix * inverse_shearing_matrix;
}
