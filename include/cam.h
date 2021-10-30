//cam.h

//#pragma once
#ifndef __CAM__
#define __CAM__

#include <random>
#include <iostream>
#include "vecmath.h"
#include "ray.h"



class Cam {
public:
	point position;
	point pointTo;
	Vec3 up;
	float aspRatio;
	float fov;
	float aperture;
	float focus;

	Vec3 cameraU;
	Vec3 cameraV;
	Vec3 cameraW;
	Vec3 vert;
	Vec3 hori;
	point llc;

	Cam();
	Cam(point position, point pointTo, Vec3 up, float aspRatio, float fov, float aperture, float focus);

	ray getRaysFromCameraPosition(float pixelU, float pixelV);
private:
	Vec3 randomfloatVec();
};


#endif
