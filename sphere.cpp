//////////////////////////////////////////////////////////
// sphere.cpp  / sphere.h                               //
// Sphere object.                                       //
// Nicholas Morash - A00378981 - nicholas.morash@smu.ca //
//////////////////////////////////////////////////////////

#include "include/sphere.h"
#include <math.h>

/* Sphere constructor   */
Sphere::Sphere(point c, float r, Material s)
{
	center = c;
	radius = r;
	trans = s.transparency;
	reflect = s.reflection;
    IOR = s.IOR;
	color = s.baseColor;
    emission = s.emission;
}

/* Ray sphere intersections*/
float Sphere::sphereIntersectQuad(ray r) {
    //Compute ray from origin to sphere center
    Vec3 oc = r.origin().sub(center);
    //Use quadratic formula
    float b = 2.0 * (r.direction().dot(oc));
    float c = (oc.dot(oc)) - (radius * radius);
    float fourAC = 4 * (r.direction().dot(r.direction())) * c;
    //Compute discriminant
    float discriminant = ((b * b) - fourAC);
    if (discriminant > 0) {

        float t0 = (((-b) - sqrt(discriminant)) / (2.0 * (r.direction().dot(r.direction()))));
        float t = t0;
        return t;
    }
    else {
        return -1;
    }
}