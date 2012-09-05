#ifndef FLATUVMESHTRIANGLE_H
#define FLATUVMESHTRIANGLE_H

/* by L.B. */
#include "flatmeshtriangle.h"

class FlatUVMeshTriangle : public FlatMeshTriangle
{
public:
    FlatUVMeshTriangle(void);
    FlatUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

    virtual FlatUVMeshTriangle*
    clone(void) const;

    FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt);

    virtual
    ~FlatUVMeshTriangle(void);

    FlatUVMeshTriangle&
    operator= (const FlatUVMeshTriangle& rhs);

    virtual bool
    hit(const Ray &ray, double &tmin, ShadeRec &sr) const;
};

#endif // FLATUVMESHTRIANGLE_H
