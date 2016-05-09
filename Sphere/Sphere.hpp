//
//  Sphere.hpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/7/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <OpenGL/gl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "shaderSetup.hpp"




class Sphere {
public:
    Sphere();
    void drawObj();
    
private:
    static bool initialized;
    static GLuint vBuffer;
    static GLuint shaderPrg;
    GLfloat *vertexData;
    GLint numVerticies;
    
    void setupGLBuffers();
    void setVertexData();
};

// Geometry Data
// OpenGL data



#endif /* Sphere_hpp */
