//
//  FluidMath.cpp
//  SimpleRayTracer
//
//  Created by Eric Knapik on 3/10/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#include "FluidMath.hpp"


// W smoothing kernal quite arbitrary
float W(glm::vec3 r, glm::vec3 rb, float h) {
    float radius = glm::length(r-rb);
    float scale = 315 / (64 * pi * pow(h,9));
    float inner = (h*h) - (radius*radius);
    return scale * pow(inner, 3);
}

// The gradient of W smoothing kernal
glm::vec3 gradientW(glm::vec3 r, glm::vec3 rb, float h) {
    float radius = glm::length(r-rb);
    float scale = -45 / (pi * pow(h, 6));
    glm::vec3 vector = glm::normalize(r-rb);
    return scale * float(pow(h-radius,2)) * vector;
}

// the graident squared of W smoothing kernal
float gradientSquaredW(glm::vec3 r, glm::vec3 rb, float h) {
    float radius = glm::length(r-rb);
    float scale = 45 / (pi * pow(h, 6));
    return scale * (h-radius);
}

/*
 // check for 0 <= radius <=
 float radius = glm::length(r-rb);
 if(0 <= radius || radius <= h) {
 return 0;
 }
*/