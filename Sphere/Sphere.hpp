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
#include "../glm/vec3.hpp"
#include "shaderSetup.hpp"


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Sphere {
public:
    Sphere();
    void drawObj();
    
    glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
    
private:
    static bool initialized;
    static GLuint vBuffer;
    static GLuint eBuffer;
    static GLuint shaderPrg;
    static GLuint vPosition;
    static GLuint transLoc;
    
    static GLfloat *vertexData;
    static GLushort *elemData;
    static GLint numVert;
    
    void setupGLBuffers();
    void setVertexData();
};

// Geometry Data
// OpenGL data



#endif /* Sphere_hpp */
