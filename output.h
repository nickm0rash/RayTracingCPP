//output.h

//#pragma once
#ifndef __OUTPUT__
#define __OUTPUT__

#include<iostream>
#include"vecmath.h"

class Output {
	public:
		//Outputs required header for PPM format.
		void header(int width, int height);

		//writes out pixel color in PPM format.
		void pixelOut(RGB pixel);
};
#endif
