//////////////////////////////////////////////////////////
// ray.cpp  / ray.h                                     //
// Ray object.                                          //
// Nicholas Morash - A00378981 - nicholas.morash@smu.ca //
//////////////////////////////////////////////////////////
#include "include/ray.h"
#include "include/vecmath.h"

/* Constructor   */
ray::ray() {}

ray::ray(point origin, Vec3 direction) {
    o = origin;
    d = direction;
}

/* Returns ray origin   */
point ray::origin() {
    return o;
}
/* Returns ray direction */
Vec3 ray::direction() {
    return d;
}

/*Returns point on ray given (time/distance)*/
point ray::pointOnRay(float t) {
    //P(t) = o + d(t)
    point p = o.add(d.scale(t));
    return p;
}