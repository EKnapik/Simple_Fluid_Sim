//
//  FluidParticle.hpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/7/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#ifndef FluidParticle_hpp
#define FluidParticle_hpp

#include "Sphere.hpp"
#include "FluidMath.hpp"

// SETUP FOR WATER
/*
 The H value is very dependant on the number of particles in the simulation
 witht the value too low the kernel functions won't work properly and with it
 too high the fluid will explode
 */
#define FLUID_NUM_PARTICLES 27
#define FLUID_PARTICLE_MASS 0.02
#define FLUID_CONSTANT_K 3.5
#define FLUID_FRICTION_MU 3.5
#define FLUID_H_VALUE .0625
#define FLUID_RADIUS 0.01685  // the particle's radius
#define FLUID_REST_DENSITY 1000

// Bounding Box
#define xMin -5.0
#define xMax 5.0
#define yMin 0.0
#define yMax 30.0
#define zMin -5.0
#define zMax 5.0

class FluidParticle: public Sphere {
public:
    FluidParticle(glm::vec3 pos);
    FluidParticle(glm::vec3 pos, float radius);
    
    void updateParticle(float timeStep, FluidParticle **fluidParticles, int numParticles);
    void updateDensity(FluidParticle **fluidParticles, int numParticles);
    void updatePressure();
    void updateGradPressureOverDensity(FluidParticle **fluidParticles, int numParticles);
    void updateViscosityGradSquaredVelocity(FluidParticle **fluidParticles, int numParticles);
    void collisionDetection(FluidParticle **fluidParticles, int numParticles, float timeStep);
    
    // position covered by inheritance
    static int _id;
    int id;
    float mass;
    float restDensity; // THIS IS BASED ON THE totalMass / totalVolume of fluid
    float density;
    float pressure;
    glm::vec3 velocity = glm::vec3(0.0);
    glm::vec3 pressureTerm = glm::vec3(0.0);
    glm::vec3 viscosityTerm = glm::vec3(0.0);
    
};
#endif /* FluidParticle_hpp */
