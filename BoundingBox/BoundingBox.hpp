//
//  BoundingBox.hpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/9/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <OpenGL/gl.h>
#include <stdio.h>
#include <iostream>
#include "../glm/vec3.hpp"
#include "shaderSetup.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Bounding Box
#define xMin -1.0
#define xMax 1.0
#define yMin 0.0
#define yMax 30.0
#define zMin -1.0
#define zMax 1.0


class BoundingBox {
public:
    BoundingBox();
    void drawObj();
    
private:
    GLuint vBuffer;
    GLuint eBuffer;
    GLuint shaderPrg;
    GLuint vPosition;
    
    GLfloat *vertexData;
    GLushort *elemData;
    GLint numVert;
    
    void setupGLBuffers();
    void setVertexData();
};



#endif /* BoundingBox_hpp */
