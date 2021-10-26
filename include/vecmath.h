//vecmath.h

//#pragma once
#ifndef __VECMATH__
#define __VECMATH__

class Vec3 {
    public:
        float x;
        float y;
        float z;

        //basic structure
        Vec3();
        Vec3(float xx, float yy, float zz);
        
        //Vector addition/subtraction.
        void add(Vec3 v);
        void sub(Vec3 v);
        
        //Scalar multiplication.
        void scale(float s);
        
        //Norm
        float magnitude();
        
        //Normalize
        void normalize();
        
        //Dot product.
        float dot(Vec3 v);
};

#endif