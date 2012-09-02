#ifndef COMPOUND_H
#define COMPOUND_H


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>
#include "shape.h"

// ------ class Compound
class Compound: public Shape {
public:
    Compound(void);
    Compound(const Compound& c);

    virtual Compound*
    clone(void) const;

    virtual
    ~Compound (void);

    Compound&
    operator= (const Compound& c);

    virtual void
    set_material(Material* material_ptr);

    virtual void
    add_object(Shape* object_ptr);

    int
    get_num_objects(void);

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& s) const;

    /* L.B. */
    virtual bool
    shadow_hit(const Ray &ray, float &tmin) const;

protected:
    std::vector<Shape*> objects;


private:
    void
    delete_objects(void);

    void
    copy_objects(const std::vector<Shape*>& rhs_objects);
};


// ------ get_num_objects
inline int
Compound::get_num_objects(void) {
    return (objects.size());
}

#endif // COMPOUND_H
