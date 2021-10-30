//material.h

//#pragma once
#ifndef __MATERIAL__
#define __MATERIAL__

#include "vecmath.h"

class Material {
public:
	float transparency; 
	float reflection;
	float IOR;
	RGB baseColor;
	RGB emission;
	
	Material();
	Material(RGB color);
	Material(float transparency, float reflectivity, float ior, RGB color, RGB emission);

};

#endif