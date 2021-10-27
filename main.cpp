#include <iostream>
#include "include/output.h"
#include "include/vecmath.h"
#include "include/ray.h"

using namespace std;
Output image;

//Setting up the scene image settings.
const float ratio = (16.0 / 9.0);
const int iWidth = 7680;
const int iHeight = static_cast<int>(iWidth / ratio);
//Other scene settings.
point origin = point(0, 0, 0);
point mainSphereCenter = point(0, 0, -1);
float sphereRadius = 0.5;
//focal plane/camera.
float sceneHeight = 2.0;
float sceneWidth = sceneHeight * ratio;
float focalDist = 1.0;
Vec3 hori = Vec3(sceneWidth, 0, 0); 
Vec3 vert = Vec3(0, sceneHeight, 0);
Vec3 halfHori = hori.scale(0.5);
Vec3 halfVert = vert.scale(0.5);
point cam = point(0, 0, focalDist);
point llc = ((origin.sub(halfHori)).sub(halfVert)).sub(cam);

//primary colors
RGB white = RGB(1, 1, 1);
RGB black = RGB(0, 0, 0);
RGB red = RGB(1, 0, 0);
RGB green = RGB(0, 1, 0);
RGB blue = RGB(0, 0, 1);

float sphereIntersect(ray& r, point& center, float radius) {
    //Compute ray from origin to sphere center
    Vec3 oc = r.origin().sub(center);
    //Use quadratic formula
    float b = 2.0 * (r.direction().dot(oc));
    float c = (oc.dot(oc)) - (radius * radius);
    float fourAC = 4 * (r.direction().dot(r.direction())) * c;
    //Compute discriminant
    float discriminant = ((b * b) - fourAC);
    if (discriminant > 0) {
        
        return (((0-b) - sqrt(discriminant)) / (2.0 * (r.direction().dot(r.direction()))));
    }
    else {
        return -1;
    }
}

RGB setColor(ray& r) {
    float root = sphereIntersect(r, mainSphereCenter, sphereRadius);
    if (root > 0) {
        Vec3 t = r.pointOnRay(root);
        Vec3 surfaceNormal = (t.sub(mainSphereCenter)).normalize();
        return RGB(surfaceNormal.x + 1, surfaceNormal.y + 1, surfaceNormal.z + 1).scale(0.5);
    }
    Vec3 rayNormalized = r.direction().normalize();
    float t = 0.5 * (rayNormalized.y + 1.0);
    RGB toWhite = RGB(1.0, 1.0, 1.0).scale(1.0 - t);
    RGB color = RGB(0, 0, 0).add(toWhite);
    return color;
}

int main() {
    image.header(iWidth, iHeight);
    for (int j = iHeight - 1; j >= 0; --j) {
        std::cerr << "\rImage lines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < iWidth; ++i) {
            float pixelU = (float)i / (iWidth - 1);
            float pixelV = (float)j / (iHeight - 1);
            Vec3 direction = llc.add(((hori.scale(pixelU)).add(vert.scale(pixelV))).sub(origin));
            ray currentRay(origin, direction);
            RGB currentPixel = setColor(currentRay);
            image.pixelOut(currentPixel);
        }
    }
}
