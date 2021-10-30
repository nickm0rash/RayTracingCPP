/**************************************************************
* This is a simple raytracer with a movable camera, reflections,
* refractions, and material support.
* 
* Still TODO: Anti-Aliasing, Fix Shadows, Depth of field.
* 
* And actual Blinn-Phong model, mine is close but not really.
* 
* Nicholas Morash - A00378981 - nicholas.morash@smu.ca
* CSCI 4471 "Computer Graphics" - Assignment 1
* 
*/



#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "include/output.h"
#include "include/vecmath.h"
#include "include/ray.h"
#include "include/sphere.h"
#include "include/material.h"
#include "include/cam.h"

//Global settings
Vec3 one = Vec3(1, 1, 1);
using namespace std;
Output image;
float pi = 3.14159265358979;
float inf = std::numeric_limits < float > ::infinity();
//const int AA_Samples = 15;  TODO: Implement Anti-Aliasing
const int renderDepth = 10;

//SETTING UP THE SCENE
//Setting up the scene image settings.
float ratio = (16.0 / 9.0);
int iWidth = 15360;
int iHeight = static_cast <int> (iWidth / ratio);

//Other scene settings.
Vec3 up = Vec3(0, 1, 0);
point origin = point(0, 0, 0);
float sphereRadius = 0.5;

//Main Sphere (sphere.h)
point mainS = point(0, -1, -6);
point secondaryS = point(0, -1.25, -4);
//Camera settings.
float fov = 30;
point position = point(0, 0, 0);
point look = mainS;
float focusDistance = sqrt((mainS.y * mainS.y) + (mainS.z * mainS.z));
float aperture = 10;

//Camera, moveable. (camera.h)
Cam camera(position, look, up, ratio, fov, aperture, focusDistance);

//Materials (transparancy, reflectivity, IOR, color, emission/light color)
Material chromeLike = Material(0, 0.9, 1.100, RGB(200.0 / 255.0, 180.0 / 255.0, 30.0 / 255.0), RGB());
Material dark = Material(0, 0.01, 1, RGB(0.1, 0.1, 0.1), RGB());
Material whitePearl = Material(0, 0.01, 1.530, RGB(0.988, 1, 0.949), RGB());
Material groundMat = Material(0, 0.005, 0, RGB(89.0/255.0, 11.0/255, 11.0/255.0), RGB());
Material light = Material(0, 0, 0, RGB(1, 1 ,1), RGB(1.0, 1.0, 1.0));

//Debug (useful information
//long numhits = 0;


/* Fall off edge - shader shades pixel based on ratio between surface normal and reflected ray.
*  This shader increses the "brightness" of a surface when it is facing the camera.
*  It significantly helps with the relfectivity effect.
*/
float shader(float fRatio, float mixa, float mixb) {
    float faceValue = 1 - fRatio;
    faceValue = pow(faceValue, 2);
    float mixedRatio = mixa * mixb;
    float mixed = mixedRatio + (faceValue * (1 - mixb));
    return mixed;
}

//Tracing of the ray and its reflections happens here, to color the ray. 
//Color is traced recursively through reflections until depth is reached.
RGB setColor(ray r, int depth, std::vector < Sphere > sList) {
    Sphere* currentSphere = NULL;
    float nearestRoot = inf;
    //Used for biasing the origin of new rays.
    float newRayBias = 0.001;
    RGB colorToOutput = RGB(0, 0, 0);
    //Checks current ray against all spheres for intersect.
    for (int i = 0; i < sList.size(); ++i) {
        float root = sList[i].sphereIntersectQuad(r);
        if (root > 0) {
            //numhits++;
            //Out of all intersects finds closest one.
            if (root < nearestRoot) {
                nearestRoot = root;
                currentSphere = &sList[i];
            }
        }
    }
    //if no sphere was hit output backround color.
    if (currentSphere == NULL) {
        //Vec3 rayNormalized = r.direction().normalize();
        //float t = 0.5 * (rayNormalized.y + 1.0);
        //RGB toLighter = RGB(0.80, 0.80, 0.80).scale(1.0 - t);
        //RGB color = RGB(0, 0, 0).add(toLighter);
        RGB background = RGB(0.8, 0.8, 0.9);
        return background;
        //return color;
    }

    //Find surface normal and creat basis.
    point intersect = r.pointOnRay(nearestRoot);
    Vec3 surfaceNormal = (intersect.sub(currentSphere->center)).normalize();
    Vec3 cameraCenter = (intersect.sub(camera.position)).normalize();

    //Check which way normal is pointing to determine if we are inside sphere.
    bool insideSphere = false;
    if (r.direction().dot(surfaceNormal) > 0) {
        surfaceNormal = surfaceNormal.scale(-1);
        insideSphere = true;
    }

    //Main recursive computatuion.
    if ((currentSphere->reflect > 0 || currentSphere->trans > 0) && depth < renderDepth) {
        //Calculating the facing ratio for shading.
        Vec3 rayCopy = r.direction();
        float facingRatio = rayCopy.dot(surfaceNormal);
        float shade = shader(facingRatio, 1.0, 0.999);

        //Determine reflection ray.
        Vec3 reflection = r.direction();
        Vec3 reflDirection = surfaceNormal.scale(2 * reflection.dot(surfaceNormal));
        reflection = (reflection.sub(reflDirection)).normalize();
        ray reflectionRay = ray(intersect.add(surfaceNormal.scale(newRayBias)), reflection);

        //Repeat until max depth or diffuse.
        RGB reflectionColor = setColor(reflectionRay, depth + 1, sList);
        RGB refractionColor = RGB(0, 0, 0);

        //If transpanrency use Snells law to determine refraction.
        if (currentSphere->trans > 0) {
            float Ni, Nt, k_2, k, coseta; //Refraction and reflection indecies, and cos(_eta_)
            //Material IOR
            Ni = 1;
            Nt = currentSphere->IOR;
            //Snell's Law. 
            float N = Ni / Nt;
            if (insideSphere) N = (1 / N);
            coseta = -(surfaceNormal.dot(r.direction()));
            k_2 = 1 - (N * N * (1 - coseta * coseta));
            k = sqrt(k_2);
            Vec3 refraction = r.direction().scale(N);
            Vec3 refrDirection = surfaceNormal.scale((N * coseta) - k);
            refraction = (refraction.add(refrDirection)).normalize();

            ////Repeat until max depth or diffuse.
            ray refractionRay = ray(intersect.sub(surfaceNormal.scale(newRayBias)), refraction);
            refractionColor = setColor(refractionRay, depth + 1, sList);
        }
        //color pixel.
        colorToOutput = ((reflectionColor.scale(shade)).add((refractionColor.scale(currentSphere->trans).scale(1 - shade)))).times(currentSphere->color);
    }
    else {
        //Either a light source or a object with no reflectivity.
        for (unsigned i = 0; i < sList.size(); ++i) {
            if (sList[i].emission.dot(sList[i].emission) > 0) {
                Vec3 lightSource = one;
                Vec3 lightDir = ((sList[i].center).sub(intersect)).normalize();
                for (int j = 0; j < sList.size(); ++j) {
                    if (i != j) {
                        //Emit new light ray, in normal direction.
                        ray newRay = ray(intersect.add(surfaceNormal.scale(newRayBias)), lightDir);
                        if (sList[j].sphereIntersectQuad(newRay) > 0) {
                            lightSource = Vec3();
                            break;
                        }
                    }
                }
                float x = intersect.dot(lightDir);
                float max = std::max((float)0, x);
                colorToOutput = colorToOutput.add(currentSphere->color.times(sList[i].emission).times(lightSource.scale(max)));
            }
            //Diffuse color
            else return colorToOutput = colorToOutput.add(currentSphere->color);
        }
    }

    //Total color.
    return colorToOutput.add(currentSphere->emission);
}

void startRender(std::vector < Sphere > sList) {
    for (int scanlines = iHeight - 1; scanlines >= 0; --scanlines) {
        std::cerr << "\rScanines left to render = " << scanlines << ' ' << std::flush;
        for (int pixel = 0; pixel < iWidth; ++pixel) {
            //for (int sample = 0; sample < AA_Samples; ++sample) {       //For anti-aliasing.
            float pixelU = ((float)pixel + 0.5) / (iWidth - 1);
            float pixelV = ((float)scanlines + 0.5) / (iHeight - 1);
            ray currentRay = camera.getRaysFromCameraPosition(pixelU, pixelV);
            RGB currentPixel = setColor(currentRay, 0, sList);
            image.pixelOut(currentPixel);
            //}
        }
    }
}

int main() {
    //Creates header in file, required for .PPM files.
    image.header(iWidth, iHeight);
    //Adding our main spheres to the list of spheres.
    std::vector < Sphere > listOfSpheres;
    Sphere mainSphere = Sphere(mainS, sphereRadius, chromeLike);
    Sphere secondary = Sphere(secondaryS, sphereRadius / 2, dark);
    listOfSpheres.push_back(mainSphere);
    listOfSpheres.push_back(secondary);
    //Creation of our ring of auxillary spheres.
    int auxSpheres = 75;
    int auxLights = 3;
    float theta = ((2 * pi) / auxSpheres);
    float radiusFromOrigin = 2.5;
    Sphere aux = Sphere(point(-100, -100, 100), 1, whitePearl);
    for (int i = 1; i < auxSpheres + 1; ++i) {
        float index = i;
        float spiral = (2 * (index / 75)) + 1;
        point auxCenter = mainS.sub(point(std::cos(i * theta), sphereRadius / 3, std::sin(i * theta)).scale(radiusFromOrigin));
        aux = Sphere((auxCenter.sub(Vec3(0, 0, 0))), (sphereRadius / 10), whitePearl);
        listOfSpheres.push_back(aux);
    }
    
    //move ground with spheres
    point groundTransform = point(mainS.sub(point(0, 10000.5, 0)));
    //add light and ground.
    Sphere ground = Sphere(groundTransform, 10000, groundMat);
    Sphere lightSource = Sphere(point(600,2000, 60), 250, light);
    listOfSpheres.push_back(ground);
    listOfSpheres.push_back(lightSource);
    //Start render.
    startRender(listOfSpheres);
    //DEBUG : cerr << iWidth * iHeight << " " << numhits << std::endl;
}