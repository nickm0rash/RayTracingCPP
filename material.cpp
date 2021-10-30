//////////////////////////////////////////////////////////
// material.cpp  / material.h                           //
// Stores useful material properties that are used in   //
// Snell's law calculations and coloring.               //
// Nicholas Morash - A00378981 - nicholas.morash@smu.ca //
//////////////////////////////////////////////////////////

#include "include/material.h"

/* Constructors    */
Material::Material() {}

Material::Material(RGB color) {
	transparency = 0;
	reflection = 0;
	IOR = 0; //index of reflection.
	baseColor = color;
	emission = RGB(0, 0, 0);
}

Material::Material(float trans, float reflect, float ior, RGB color, RGB emis) {
	transparency = trans;
	reflection = reflect;
	IOR = ior;
	baseColor = color;
	emission = emis; // > 0 means a light source.
}
