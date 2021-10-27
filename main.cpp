#include <iostream>
#include "include/output.h"
#include "include/vecmath.h"
#include "include/ray.h"

using namespace std;
Output image;

//Setting up the scene image settings.
const float ratio = (16.0 / 10.0);
const int width = 1000;
const int height = static_cast<int>(width / ratio);
//Other scene settings.
const point origin = point();

//primary colors
const RGB white = RGB(1, 1, 1);
const RGB black = RGB(0, 0, 0);
const RGB red = RGB(1, 0, 0);
const RGB green = RGB(0, 1, 0);
const RGB blue = RGB(0, 0, 1);



int main() {
    image.header(width, height);
    for (int j = height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            RGB pixel_color(red);
            image.pixelOut(pixel_color);
        }
    }
}
