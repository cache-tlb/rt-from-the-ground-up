#ifndef SCENE_H
#define SCENE_H

// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory.

#include <vector>

#include "viewplane.h"
#include "rgbcolor.h"
#include "tracer.h"
#include "shape.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "ambient.h"

using namespace std;

class Scene {
public:
    ViewPlane				vp;
    RGBColor				background_color;
    Tracer*					tracer_ptr;
    Light*   				ambient_ptr;
    Camera*					camera_ptr;
    vector<Shape*>          objects;
    vector<Light*> 			lights;

    RGBColor*               render_res;

public:
    Scene(void);
    ~Scene(void);

    void
    add_object(Shape* object_ptr);

    void
    add_light(Light* light_ptr);

    void
    set_ambient_light(Light* light_ptr);

    void
    set_camera(Camera* c_ptr);

    void
    build(void);

    /*void
    render_scene(void) const;*/

    RGBColor
    max_to_one(const RGBColor& c) const;

    RGBColor
    clamp_to_color(const RGBColor& c) const;

    void
    display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

    ShadeRec
    hit_objects(const Ray& ray);


private:
    void
    delete_objects(void);

    void
    delete_lights(void);
};

// ------ add_object
inline void
Scene::add_object(Shape* object_ptr) {
    objects.push_back(object_ptr);
}


// ------ add_light
inline void
Scene::add_light(Light* light_ptr) {
    lights.push_back(light_ptr);
}


// ------ set_ambient_light
inline void
Scene::set_ambient_light(Light* light_ptr) {
    ambient_ptr = light_ptr;
}

// ------ set_camera
inline void
Scene::set_camera(Camera* c_ptr) {
    camera_ptr = c_ptr;
}

#endif // SCENE_H
