//sphere.h

//#pragma once
#ifndef __SPHERE__
#define __SPHERE__

#include "vecmath.h"
#include "material.h"
#include "ray.h"


class Sphere {
public:
	point center;
	float radius;
	float trans;
	float reflect;
	float IOR;
	RGB color;
	RGB emission;

	Sphere(point c, float r, Material s);
	float sphereIntersectQuad(ray r);
};


#endif