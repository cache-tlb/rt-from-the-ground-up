#ifndef AREALIGHTING_H
#define AREALIGHTING_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "tracer.h"

class AreaLighting: public Tracer {
public:
    AreaLighting(void);
    AreaLighting(Scene* _scenePtr);

    virtual
    ~AreaLighting(void);

    virtual RGBColor
    trace_ray(const Ray ray, const int depth) const;
};


#endif // AREALIGHTING_H
