//
//  FluidMath.hpp
//  SimpleRayTracer
//
//  Created by Eric Knapik on 3/10/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#ifndef FluidMath_hpp
#define FluidMath_hpp

#include <stdio.h>
#include "../glm/vec3.hpp"
#include "../glm/glm.hpp"
#include <math.h>

// #define fluid constants
#define pi 3.14159265

// The fluid smoothing kernal functions

float W(glm::vec3 r, glm::vec3 rb, float h);

glm::vec3 gradientW(glm::vec3 r, glm::vec3 rb, float h);

float gradientSquaredW(glm::vec3 r, glm::vec3 rb, float h);

#endif /* FluidMath_hpp */
