#ifndef RAY_H
#define RAY_H

#include "point3d.h"
#include "vector3d.h"

class Ray {
public:
    Point3D			o;  	// origin
    Vector3D		d; 		// direction

public:
    Ray(void);
    Ray(const Point3D& origin, const Vector3D& dir);
    Ray(const Ray& ray);

    ~Ray(void);

    Ray&
    operator= (const Ray& rhs);

};

#endif // RAY_H
