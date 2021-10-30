//vecmath.h

//#pragma once
#ifndef __VECMATH__
#define __VECMATH__

class Vec3 { 
    public:
        //Structure
        float x;
        float y;
        float z;

        //Constructors
        Vec3();
        Vec3(float xx, float yy, float zz);
        //Vector addition/subtraction.
        Vec3 add(Vec3 v);
        Vec3 sub(Vec3 v);
        Vec3 times(Vec3 v);
        
        //Scalar multiplication.
        Vec3 scale(float s);
        
        //Norm
        float magnitude();
        
        //Normalize
        Vec3 normalize();
        
        //Dot product.
        float dot(Vec3 v);

        //Cross product.
        Vec3 cross(Vec3 v);
};

//Aliases
using RGB = Vec3;   //color (R, G, B)
using point = Vec3; //Helpful for visualizing rays and intercepts.

#endif