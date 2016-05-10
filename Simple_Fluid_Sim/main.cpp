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
#include <unistd.h>
#include <time.h>
#include "Sphere.hpp"
#include "FluidParticle.hpp"
#include "BoundingBox.hpp"


// 16 x 9
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define MICRO_FRAME_TIME 33333
#define TIME_DELTA 0.03333

// GLOBAL VARIABLES
FluidParticle *particle;
FluidParticle **particles;
int numParticles;
BoundingBox *box;
int waitTime;


// FUNCTIONS
void initOpenGL(void);
void render(void);
void initParticles(void);
void updateParticles(void);



int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Simple Fluid Simulation");
    glutDisplayFunc(render);
    initOpenGL();
    
    // particle = new FluidParticle(glm::vec3(0.0, 0.0, 0.0));
    box = new BoundingBox();
    initParticles();
    
    waitTime = 0;
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
    box->drawObj();
    //particle->drawObj();
    //particle->pos += glm::vec3(0.0, -0.1, 0.0);
    for(int i = 0; i < numParticles; i++) {
        particles[i]->drawObj();
    }
    updateParticles();
    
    
    t = clock() - t;
    renderTime = ((float)t)/CLOCKS_PER_SEC;
    printf("Render took (%.4f seconds)\n", renderTime);
    
    waitTime = MICRO_FRAME_TIME - t;
    if(waitTime > 0) { usleep(waitTime); } // sleep for n microseconds
    
    glutSwapBuffers();
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#!#!#!#!#!#!
    glutPostRedisplay();
}



void initParticles(void) {
    numParticles = FLUID_NUM_PARTICLES;
    particles = new FluidParticle *[numParticles];
    
    float currX = 0.0;
    float currY = 0.4;
    float currZ = 0.0;
    
    int tmp = powf(numParticles, float(1.0/3.0));
    int count = 0;
    for(int i = 0; i < tmp; i++) {
        currZ = 0.0;
        for(int j = 0; j < tmp; j++) {
            currX = 0.0;
            for(int w = 0; w < tmp; w++) {
                particles[count] = new FluidParticle(glm::vec3(currX, currY, currZ));
                count++;
                currX += (2*FLUID_RADIUS);
            }
            currZ -= (2*FLUID_RADIUS);
        }
        currY += (2*FLUID_RADIUS);
    }
}



void updateParticles(void) {
    // TODO  THERE SHOULD BE A PARTICLE ENGINEE....
    // Update the density and pressure of each particle
    for(int i = 0; i < numParticles; i++) {
        particles[i]->updateDensity(particles, numParticles);
        // printf("ID: %d, Density: %.2f\n", this->scene->particles[i]->id, this->scene->particles[i]->density);
    }
    for(int i = 0; i < numParticles; i++) {
        particles[i]->updatePressure();
        // printf("ID: %d, Pressure: %.2f\n", this->scene->particles[i]->id, this->scene->particles[i]->pressure);
    }
    // update the pressure over density term for each particle
    for(int i = 0; i < numParticles; i++) {
        particles[i]->updateGradPressureOverDensity(particles, numParticles);
    }
    // update the viscosity term for each particle
    for(int i = 0; i < numParticles; i++) {
        particles[i]->updateViscosityGradSquaredVelocity(particles, numParticles);
    }
    // Now move the particle
    for(int i = 0; i < numParticles; i++) {
        particles[i]->updateParticle(TIME_DELTA, particles, numParticles);
    }
    // -----------FLUID STUFF  END------
    // collide particles with the scene objects
    for(int i = 0; i < numParticles; i++) {
        particles[i]->boundsConstraint();
    }
    //for(int i = 0; i < numParticles; i++) {
    //    particles[i]->collisionDetection(particles, numParticles, TIME_DELTA);
    //}
   
}