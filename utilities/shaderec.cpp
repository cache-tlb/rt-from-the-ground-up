// this file contains the definition of the class ShadeRec

// there is no default constructor as the World reference has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "constants.h"
#include "shaderec.h"
#include "material.h"

// ------ constructor
ShadeRec::ShadeRec(Scene& wr)
    : hit_an_object(false),
      material_ptr(NULL),
      hit_point(),
      local_hit_point(),
      normal(),
      ray(),
      depth(0),
      color(black),
      t(0.0),
      u(0.0),
      v(0.0),
      w(wr)

{}

// ------ copy constructor
ShadeRec::ShadeRec(const ShadeRec& sr)
    : hit_an_object(sr.hit_an_object),
      material_ptr(sr.material_ptr),
      hit_point(sr.hit_point),
      local_hit_point(sr.local_hit_point),
      normal(sr.normal),
      ray(sr.ray),
      depth(sr.depth),
      color(sr.color),
      t(sr.t),
      u(sr.u),
      v(sr.v),
      w(sr.w)

{
    /*if(sr.material_ptr){
        material_ptr = sr.material_ptr->clone();
    }
    else{
        material_ptr = NULL;
    }*/
}

// ------ destructor
ShadeRec::~ShadeRec(void) {
    /*if (material_ptr) {
        delete material_ptr;
        material_ptr = NULL;
    }*/
}
