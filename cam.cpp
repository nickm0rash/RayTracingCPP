//////////////////////////////////////////////////////////
// cam.cpp  / cam.h                                     //
// Camera object that stores settings and position.     //
// Nicholas Morash - A00378981 - nicholas.morash@smu.ca //
//////////////////////////////////////////////////////////

#include "include/cam.h"
#include <ostream>

/* Default camera constructor, with position at the origin.  */
Cam::Cam() {
	point pos = point(0, 0, -1);
	point pntTo = point();
	Vec3 upDir = Vec3(0, 1, 0);
	float aspect = 16.0 / 9.0;
	float fov = 35.0;
	float aprtur = 0;
	float foc = 1.0;
	Cam(pos, pntTo, upDir, aspect, fov, aprtur, foc);
}

/*Camera constructor.   */
Cam::Cam(point position, point pointTo, Vec3 up, float aspectRatio, float fov, float a, float focus) {
	//Scene settings.
	float pi = 3.14159265358979;
	float angle = tan(((pi / 2) * fov) / 180);
	float sceneHeight = 2.0 * angle;
	float sceneWidth = sceneHeight * aspectRatio;
	aperture = a;
	//Orthonormal basis.
	cameraW = (position.sub(pointTo)).normalize();
	cameraU = (up.cross(cameraW)).normalize();
	cameraV = cameraW.cross(cameraU);
	//Image plane
	vert = cameraV.scale(focus * sceneHeight);
	hori = cameraU.scale(focus * sceneWidth);
	llc = position.sub(hori.scale(0.5));
	llc = llc.sub(vert.scale(0.5));
	//focus point for blur TO BE IMPLEMENTED  ********
	llc = llc.sub(cameraW.scale(focus));
}

/*If camera position is modified this will adjust the dimentions
 * and coordinate system of the new image plane.*/
ray Cam::getRaysFromCameraPosition(float pixelU, float pixelV) {
	Vec3 scaledH = hori.scale(pixelU);
	Vec3 scaledV = vert.scale(pixelV);
	point newDirection = llc.add((((hori.scale(pixelU)).add(vert.scale(pixelV))).sub(position)));
	ray currentRay = ray(position, newDirection);
	return currentRay;
}

//Used for antialiasing *** NOT IMPLEMENTED (OUT OF TIME),
// might be complete for demo but not for submission.
// 
//Vec3 Cam::randomfloatVec() {
//	std::random_device rdID;
//	std::mt19937 mt(rdID());
//	std::uniform_real_distribution<float> random(-1.0, 1.0);
//	while (true) {
//		Vec3 rndm = Vec3(random(rdID), random(rdID), 0);
//		if ((rndm.magnitude() * rndm.magnitude()) >= 1) continue;
//		return rndm;
//	}
//}