#include <iostream>
#include "include/output.h"

void Output::header(int width, int height) {
	std::cout << "P3\n" << width << ' ' << height << "\n255" << std::endl;
}

void Output::pixelOut(RGB pixel) {
	float r, g, b;
	//Clamp pixel to 1 (255) or 0 (0);
	//RED
	if (pixel.x <= 1 && pixel.x >= 0) {
		r = pixel.x;
	}
	else if (pixel.x < 0){
		r = 0.0;
	}
	else {
		r = 1.0;
	}
	//GREEN
	if (pixel.y <= 1 && pixel.y >= 0) {
		g = pixel.y;
	}
	else if (pixel.y < 0) {
		g = 0.0;
	}
	else {
		g = 1.0;
	}
	//BLUE
	if (pixel.z <= 1 && pixel.z >= 0) {
		b = pixel.z;
	}
	else if (pixel.z < 0) {
		b = 0.0;
	}
	else {
		b = 1.0;
	}

	//cast to int conversion rounds down, thus 255.9999 is used.
	int R, G, B;
	R = static_cast<int>(255.9999 * r);
	G = static_cast<int>(255.9999 * g);
	B = static_cast<int>(255.9999 * b);

	//output PPM image line.
	std::cout << R << " " << G << " " << B << std::endl;
}
