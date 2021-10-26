#include <iostream>
#include "include/output.h"

//TODO: create image using casted ray calulated pixels.
//default "Ray Tracing in One Weekend" PPM file creator.
//https://raytracing.github.io/books/RayTracingInOneWeekend.html
void Output::image(int width, int height) {
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {

			float r = (float)i / (width-1);
            float g = (float)j / (height-1);
            float b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
