#ifndef SHADEREC_H
#define SHADEREC_H

// this file contains the declaration of the class ShadeRec

#include <vector>

class Material;
class Scene;

// We need the following as #includes instead of forward class declarations,
// because we have the objects themselves, not pointers or references

#include "point3d.h"
#include "normal.h"
#include "ray.h"
#include "rgbcolor.h"

class ShadeRec {
public:

    bool				hit_an_object;		// did the ray hit an object?
    Material* 			material_ptr;		// pointer to the nearest object's material
    Point3D 			hit_point;			// world coordinates of intersection
    Point3D				local_hit_point;	// world coordinates of hit point on untransformed object (used for texture transformations)
    Normal				normal;				// normal at hit point
    Ray					ray;				// required for specular highlights and area lights
    int					depth;				// recursion depth
    RGBColor			color;				// used in the Chapter 3 only
    double				t;					// ray parameter
    float				u;					// texture coordinate
    float				v;					// texture coordinate
    Scene&				w;					// world reference

    ShadeRec(Scene& wr);					// constructor
    ShadeRec(const ShadeRec& sr);			// copy constructor
    ~ShadeRec(void);						// destructor

};
#endif // SHADEREC_H
