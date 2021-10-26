//////////////////////////////////////////////////////////
// vecmath.cpp                                          //
// Simple vector utility fucntions.                     //
// Nicholas Morash - A00378981 - nicholas.morash@smu.ca //
//////////////////////////////////////////////////////////


#include <iostream>
#include <math.h>
#include "include/vecmath.h"

//Zero'd vector constructor
Vec3::Vec3() : x(0), y(0), z(0) {}

//Vector constructor
Vec3::Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

//Vector addition.
void Vec3::add(Vec3 v) {
    x = x + v.x;
    y = y + v.y;
    z = z + v.z;
}

//Vector subtraction.
void Vec3::sub(Vec3 v) {
    x = x - v.x;
    y = y - v.y;
    z = z - v.z;
}

//Vector multiplication (scalar).
void Vec3::scale(float s) {
    x = s * x;
    y = s * y;
    z = s * z; 
}

//Vector norm.
float Vec3::magnitude() {
    float m = std::sqrt((x * x) + (y * y) + (z * z));
    return m;
}

//Vector normalization.
void Vec3::normalize() {
    float m = std::sqrt((x * x) + (y * y) + (z * z));
    x = x / m;
    y = y / m;
    z = z / m;
}

//Dot product.
float Vec3::dot(Vec3 v) {
    float d = ((x * v.x) + (y * v.y) + (z * v.z));
    return d;
}