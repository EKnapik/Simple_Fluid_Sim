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


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Sphere {
public:
    Sphere();
    void drawObj();
    
private:
    static bool initialized;
    static GLuint vBuffer;
    static GLuint eBuffer;
    static GLuint shaderPrg;
    static GLuint vPosition;
    
    static GLfloat *vertexData;
    static GLushort *elemData;
    static GLint numVert;
    
    void setupGLBuffers();
    void setVertexData();
};

// Geometry Data
// OpenGL data



#endif /* Sphere_hpp */
