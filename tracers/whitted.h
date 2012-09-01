#ifndef WHITTED_H
#define WHITTED_H

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class Whitted: public Tracer {
public:
    Whitted(void);
    Whitted(Scene* _scenePtr);

    virtual
    ~Whitted(void);

    virtual RGBColor
    trace_ray(const Ray ray, const int depth) const;
};


#endif // WHITTED_H
