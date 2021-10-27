#include "include/ray.h"
#include "include/vecmath.h"

ray::ray() {}

ray::ray(point origin, Vec3 direction) {
    o = origin;
    d = direction;
}

point ray::origin() {
    return o;
}

Vec3 ray::direction() {
    return d;
}

point ray::pointOnRay(float t) {
    //P(t) = o + d(t)
    point p = o.add(d.scale(t));
    return p;
}