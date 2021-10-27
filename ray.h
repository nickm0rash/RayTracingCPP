//ray.h

//#pragma once
#ifndef __RAY__
#define __RAY__

#include "vecmath.h"

class ray {
    public:
        point o;
        Vec3 d; 

        ray();

        ray(point origin, Vec3 direction);

        point origin();

        Vec3 direction();

        //return a point on the ray.
        point pointOnRay(float t);
};

#endif