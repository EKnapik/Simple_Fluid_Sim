//
//  Sphere.cpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/7/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#include "Sphere.hpp"

// Initalize Static values
bool Sphere::initialized = false;
GLuint Sphere::vBuffer = 0;
GLuint Sphere::shaderPrg = 0;
GLuint Sphere::vPosition = 0;
GLfloat *Sphere::vertexData = NULL;
GLint Sphere::numVert = 0;


Sphere::Sphere() {
    setupGLBuffers();
}

void Sphere::drawObj() {
    glUseProgram(Sphere::shaderPrg);
    glBindBuffer(GL_ARRAY_BUFFER, Sphere::vBuffer);
    glEnableVertexAttribArray( Sphere::vPosition );
    // pass the vertex to the shader the offset is 0 because it is first
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    // PASS OTHER SHADER INFO
    
    glDrawElements( GL_TRIANGLES, Sphere::numVert, GL_UNSIGNED_SHORT, (void *)0 );
}


void Sphere::setupGLBuffers() {
    if(Sphere::initialized) { // no need to resetup
        return;
    }
    setVertexData(); // set the vertex data before using
    size_t dataSize = Sphere::numVert * 4 * sizeof(GLfloat);
    
    // vertex data
    glGenBuffers(1, &Sphere::vBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Sphere::vBuffer);
    glBufferData(GL_ARRAY_BUFFER, dataSize, Sphere::vertexData, GL_STATIC_DRAW);
    
    // shader program
    Sphere::shaderPrg = shaderSetup("Sphere.vert", "Sphere.frag");
    // TODO SETUP VERTEX POSITIONAL DATA AND STUFF
    Sphere::vPosition = glGetAttribLocation(Sphere::shaderPrg, "vPosition" );
    
    Sphere::initialized = true;
}


void Sphere::setVertexData() {
    
    GLfloat verticies[] = {
        0.00, 0.26, -0.43, 1,
        0.26, -0.43, 1.00, 1,
        -0.43, 1.00, -0.15, 1,
        1.00, -0.15, 0.40, 1,
        -0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, 0.15, 1,
        1.00, 0.15, 0.40, 1,
        0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, -0.15, 1,
        1.00, -0.15, 0.40, 1,
        -0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, -0.26, 1,
        1.00, -0.26, 0.43, 1,
        -0.26, 0.43, 0.00, 1,
        0.43, 0.00, 1.00, 1,
        0.00, 1.00, 0.00, 1,
        1.00, 0.00, 0.50, 1,
        0.00, 0.50, 0.00, 1,
        0.50, 0.00, 1.00, 1,
        0.00, 1.00, 0.15, 1,
        1.00, 0.15, 0.40, 1,
        0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, 0.00, 1,
        1.00, 0.00, 0.50, 1,
        0.00, 0.50, 0.00, 1,
        0.50, 0.00, 1.00, 1,
        0.00, 1.00, 0.26, 1,
        1.00, 0.26, 0.43, 1,
        0.26, 0.43, 0.00, 1,
        0.43, 0.00, 1.00, 1,
        0.00, 1.00, -0.15, 1,
        1.00, -0.15, 0.40, 1,
        -0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, 0.00, 1,
        1.00, 0.00, 0.50, 1,
        0.00, 0.50, 0.00, 1,
        0.50, 0.00, 1.00, 1,
        0.00, 1.00, 0.15, 1,
        1.00, 0.15, 0.40, 1,
        0.15, 0.40, -0.25, 1,
        0.40, -0.25, 1.00, 1,
        -0.25, 1.00, 0.00, 1,
        1.00, 0.00, 0.26, 1,
        0.00, 0.26, 0.43, 1,
        0.26, 0.43, 1.00, 1,
        0.43, 1.00, 0.15, 1,
        1.00, 0.15, 0.40, 1,
        0.15, 0.40, 0.25, 1,
        0.40, 0.25, 1.00, 1,
        0.25, 1.00, -0.15, 1,
        1.00, -0.15, 0.40, 1,
        -0.15, 0.40, 0.25, 1,
        0.40, 0.25, 1.00, 1,
        0.25, 1.00, 0.15, 1,
        1.00, 0.15, 0.40, 1,
        0.15, 0.40, 0.25, 1,
        0.40, 0.25, 1.00, 1,
        0.25, 1.00, 0.26, 1,
        1.00, 0.26, 0.43, 1,
        0.26, 0.43, 0.00, 1,
        0.43, 0.00, 1.00, 1,
        0.00, 1.00, 0.00, 1,
        1.00, 0.00, 0.50, 1,
        0.00, 0.50, 0.00, 1,
        0.50, 0.00, 1.00, 1,
        0.00, 1.00, -0.15, 1,
        1.00, -0.15, 0.40, 1,
        -0.15, 0.40, 0.25, 1,
        0.40, 0.25, 1.00, 1,
        0.25, 1.00, 0.00, 1,
        1.00, 0.00, 0.50, 1,
        0.00, 0.50, 0.00, 1,
        0.50, 0.00, 1.00, 1,
        0.00, 1.00, -0.26, 1,
        1.00, -0.26, 0.43, 1};
    Sphere::numVert = 80;
    
    size_t dataSize = sizeof(GLfloat) * Sphere::numVert * 4;
    Sphere::vertexData = new GLfloat[Sphere::numVert * 4];
    memcpy( Sphere::vertexData, verticies, dataSize );
}