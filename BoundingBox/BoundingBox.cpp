//
//  BoundingBox.cpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/9/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#include "BoundingBox.hpp"



BoundingBox::BoundingBox() {
    this->setupGLBuffers();
}


void BoundingBox::drawObj() {
    glUseProgram(this->shaderPrg);
    glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eBuffer);
    glEnableVertexAttribArray( this->vPosition );
    // pass the vertex to the shader the offset is 0 because it is first
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    // PASS OTHER SHADER INFO
    
    glDrawElements( GL_LINE_STRIP, this->numVert, GL_UNSIGNED_SHORT, (void *)0 );
}



void BoundingBox::setupGLBuffers() {
    setVertexData(); // set the vertex data before using
    size_t dataSize = this->numVert * 4 * sizeof(GLfloat);
    
    // vertex data
    glGenBuffers(1, &this->vBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
    glBufferData(GL_ARRAY_BUFFER, dataSize, this->vertexData, GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->eBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numVert * sizeof(GLushort), this->elemData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // shader program
    this->shaderPrg = shaderSetup("BoundingBox.vert", "BoundingBox.frag");
    // TODO SETUP VERTEX POSITIONAL DATA AND STUFF
    this->vPosition = glGetAttribLocation(this->shaderPrg, "vPosition" );
    
}



void BoundingBox::setVertexData() {
    
    GLfloat verticies[] = {
        xMin, yMin, zMax, 1.0,
        xMax, yMin, zMax, 1.0,
        xMax, yMin, zMin, 1.0,
        xMin, yMin, zMin, 1.0,
        xMin, yMin, zMax, 1.0,
        xMin, yMax, zMax, 1.0,
        xMin, yMax, zMin, 1.0,
        xMin, yMin, zMin, 1.0,
        xMax, yMin, zMin, 1.0,
        xMax, yMax, zMin, 1.0,
        xMax, yMax, zMax, 1.0,
        xMax, yMin, zMax, 1.0
    };
    this->numVert = 12;
    
    size_t dataSize = sizeof(GLfloat) * this->numVert * 4;
    this->vertexData = new GLfloat[this->numVert * 4];
    memcpy( this->vertexData, verticies, dataSize );
    
    this->elemData = new GLushort[this->numVert];
    for(int i=0; i < this->numVert; i++ ) {
        this->elemData[i] = i;
    }
    
}