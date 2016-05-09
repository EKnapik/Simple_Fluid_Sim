//
//  main.cpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/7/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <time.h>
#include "Sphere.hpp"



// 16 x 9
#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

Sphere *sphere;

void initOpenGL(void);
void render(void);

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Simple Fluid Simulation");
    glutDisplayFunc(render);
    initOpenGL();
    
    sphere = new Sphere();
    
    glutMainLoop();
    return 0; // Cause GLUT allows us to even get back here...... (it doesn't)
}



void initOpenGL(void) {
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE | GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glCullFace(GL_FRONT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    return;
}


void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // poll events
    // bind and draw
    clock_t t;
    t = clock();
    float renderTime;
    // DO SOMETHING
    
    sphere->drawObj();
    
    t = clock() - t;
    renderTime = t;
    printf("Render took (%.4f seconds)\n",((float)renderTime)/CLOCKS_PER_SEC);
    glutSwapBuffers();
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#!#!#!#!#!#!
    // glutPostRedisplay();
}



/*
 Render Loop
 Object
    How to render it
 Step Function
 */
