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
Vec3 Vec3::add(Vec3 v) {
    float xx = x + v.x;
    float yy = y + v.y;
    float zz = z + v.z;
    Vec3 sum = Vec3(xx, yy, zz);
    return sum;
}

//Vector subtraction.
Vec3 Vec3::sub(Vec3 v) {
    float xx = x - v.x;
    float yy = y - v.y;
    float zz = z - v.z;
    Vec3 diff = Vec3(xx, yy, zz);
    return diff;
}

//Vector multiplication (scalar).
Vec3 Vec3::scale(float s) {
    float xx = s * x;
    float yy = s * y;
    float zz = s * z;
    Vec3 scaled = Vec3(xx, yy, zz);
    return scaled;
}

//Vector norm.
float Vec3::magnitude() {
    float m = std::sqrt((x * x) + (y * y) + (z * z));
    return m;
}

//Vector normalization.
Vec3 Vec3::normalize() {
    float m = std::sqrt((x * x) + (y * y) + (z * z));
    float xx = x / m;
    float yy = y / m;
    float zz = z / m;
    Vec3 normalized = Vec3(xx, yy, zz);
    return normalized;
}

//Dot product.
float Vec3::dot(Vec3 v) {
    float d = ((x * v.x) + (y * v.y) + (z * v.z));
    return d;
}