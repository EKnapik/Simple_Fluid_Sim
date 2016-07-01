//
//  FluidParticle.cpp
//  Simple_Fluid_Sim
//
//  Created by Eric Knapik on 5/7/16.
//  Copyright © 2016 EKnapik. All rights reserved.
//

#include "FluidParticle.hpp"

// Initialize Static data
int FluidParticle::_id = 0;

FluidParticle::FluidParticle() : Sphere() {
    // used for data locality initalization
}

FluidParticle::FluidParticle(glm::vec3 pos) : Sphere() {
    this->id = FluidParticle::_id++;
    this->pos = pos;
    this->radius = FLUID_RADIUS;
    
    this->density = 0.0;
    this->pressure = 0.0;
    this->mass = FLUID_PARTICLE_MASS;
    this->restDensity = FLUID_REST_DENSITY;
}

FluidParticle::FluidParticle(glm::vec3 pos, float radius) : Sphere() {
    this->id = FluidParticle::_id++;
    this->pos = pos;
    this->radius = radius;
    
    this->density = 0.0;
    this->pressure = 0.0;
    // MASS AND DENsity NEED TO BE CALCULATED
    this->mass = FLUID_PARTICLE_MASS;
    this->restDensity = FLUID_REST_DENSITY;
}


void FluidParticle::initParticle(glm::vec3 pos) {
    this->id = FluidParticle::_id++;
    this->pos = pos;
    this->radius = FLUID_RADIUS;
    
    this->density = 0.0;
    this->pressure = 0.0;
    this->mass = FLUID_PARTICLE_MASS;
    this->restDensity = FLUID_REST_DENSITY;
}

/*
 * This is applying the physics for this particle for this time delta
 * the current particle should not be in the array of particles given
 */
void FluidParticle::updateParticle(float timeStep, FluidParticle *fluidParticles, int numParticles) {
    glm::vec3 gravity = glm::vec3(0.0, -9.8, 0.0);
    
    // solve for the change in velocity at this time according to Navier-Stokes
    glm::vec3 dvdt = gravity - this->pressureTerm + this->viscosityTerm;
    
    // printf("Acceleration: %.2f, %.2f, %.2f\n", dvdt.x, dvdt.y, dvdt.z);
    // Update with Semi-implicit Euler integration
    this->velocity += dvdt * timeStep;
    // printf("TimeStep: %.2f\n", timeStep);
    // printf("Velocity: %.2f, %.2f, %.2f\n", this->velocity.x, this->velocity.y, this->velocity.z);
    this->pos += this->velocity * timeStep;
    // printf("Position: %.2f, %.2f, %.2f\n", this->pos.x, this->pos.y, this->pos.z);
    // doing fluid fluid collision detection here
    collisionDetection(fluidParticles, numParticles, timeStep);
}

/*
 * the current particle should not be in the array of particles given
 */
void FluidParticle::updateDensity(FluidParticle *fluidParticles, int numParticles) {
    float density = 0.0;
    float dist;
    for(int i = 0; i < numParticles; i++) {
        if(this->id != fluidParticles[i].id) {
            dist = glm::length(this->pos - fluidParticles[i].pos);
            if(dist < MAX_DISTANCE) {
                density += fluidParticles[i].mass * W(this->pos, fluidParticles[i].pos, FLUID_H_VALUE);
            }
        }
    }
    this->density = density;
}


void FluidParticle::updatePressure() {
    this->pressure = FLUID_CONSTANT_K * (this->density - this->restDensity);
}


/* The gradient pressure of a particle divided by the density of that particle
 * This is an estimation method using smoothing kernals
 * the current particle should not be in the array of particles given
 */
void FluidParticle::updateGradPressureOverDensity(FluidParticle *fluidParticles, int numParticles) {
    glm::vec3 result = glm::vec3(0.0);
    float pressureScale;
    float dist;
    for(int i = 0; i < numParticles; i++) {
        if(this->id != fluidParticles[i].id) {
            dist = glm::length(this->pos - fluidParticles[i].pos);
            if(dist < MAX_DISTANCE) {
                pressureScale = (this->pressure / (this->density * this->density));
                pressureScale += (fluidParticles[i].pressure / (fluidParticles[i].density * fluidParticles[i].density));
                result += fluidParticles[i].mass * pressureScale * gradientW(this->pos, fluidParticles[i].pos, FLUID_H_VALUE);
            }
        }
    }
    this->pressureTerm = result;
}

/* The viscosity times the squared gradient of velocity for a particle
 * This is an estimation method using smoothing kernals
 * the current particle should not be in the array of particles given
 */
void FluidParticle::updateViscosityGradSquaredVelocity(FluidParticle *fluidParticles, int numParticles) {
    glm::vec3 result = glm::vec3(0.0);
    float viscosityScale = FLUID_FRICTION_MU;
    float dist;
    glm::vec3 velocityVar;
    for(int i = 0; i < numParticles; i++) {
        if(this->id != fluidParticles[i].id) {
            dist = glm::length(this->pos - fluidParticles[i].pos);
            if(dist < MAX_DISTANCE) {
                velocityVar = (fluidParticles[i].velocity - this->velocity) / fluidParticles[i].density;
                result += fluidParticles[i].mass * velocityVar * gradientSquaredW(this->pos, fluidParticles[i].pos, FLUID_H_VALUE);
            }
        }
    }
    result *= viscosityScale;
    
    this->viscosityTerm = result;
}


/* Since we know the particles that are close to this one we can do collision
 * collision detection with the nearby particles
 * The collision 'mirror' reflection was taken from a paper that uses the twice
 * the checking distance for collision, the distance to the collision, the normal
 * it is similar to a perfect mirror reflection but through testing looks better
 * for water
 */
void FluidParticle::collisionDetection(FluidParticle *fluidParticles, int numParticles, float timeStep) {
    // Check Bounding Box
    float dist;
    for(int i = 0; i < numParticles; i++) {
        if(this->id != fluidParticles[i].id) {
            dist = glm::length(this->pos - fluidParticles[i].pos);
            if(dist < MAX_DISTANCE) {
                collisionHandle(fluidParticles[i], dist);
            }
        }
    }
}

void FluidParticle::collisionHandle(FluidParticle particle) {
    float dist = glm::length(this->pos - particle.pos) - this->radius - particle.radius;
    float epsilon = 0.0001;
    if(dist < epsilon) {
        glm::vec3 particleNorm = glm::normalize(this->pos - particle.pos);
        // change the velocities
        this->velocity = glm::reflect(this->velocity, particleNorm) * float(0.9);
        particle.velocity = glm::reflect(particle.velocity, -particleNorm) * float(0.9);
        // move outside of the object
        this->pos += particleNorm*(dist+epsilon);
        particle.pos += -particleNorm*(dist+epsilon);
    }
}

void FluidParticle::collisionHandle(FluidParticle particle, float distance) {
    float dist =  distance - this->radius - particle.radius;
    float epsilon = 0.0001;
    if(dist < epsilon) {
        glm::vec3 particleNorm = glm::normalize(this->pos - particle.pos);
        // change the velocities
        this->velocity = glm::reflect(this->velocity, particleNorm) * float(0.9);
        particle.velocity = glm::reflect(particle.velocity, -particleNorm) * float(0.9);
        // move outside of the object
        this->pos += particleNorm*(dist+epsilon);
        particle.pos += -particleNorm*(dist+epsilon);
    }
}

void FluidParticle::boundsConstraint() {
    float epsilon = 0.0166;
    bool fixed = false;
    glm::vec3 norm;
    if(this->pos.x < xMin) {
        this->pos.x = xMin + epsilon;
        fixed = true;
        norm = glm::vec3(1.0, 0.0, 0.0);
    }
    if(this->pos.x > xMax) {
        this->pos.x = xMax - epsilon;
        fixed = true;
        norm = glm::vec3(-1.0, 0.0, 0.0);
    }
    if(this->pos.y < yMin) {
        this->pos.y = yMin + epsilon;
        fixed = true;
        norm = glm::vec3(0.0, 1.0, 0.0);
    }
    if(this->pos.y > yMax) {
        this->pos.y = yMax - epsilon;
        fixed = true;
        norm = glm::vec3(0.0, -1.0, 0.0);
    }
    if(this->pos.z < zMin) {
        this->pos.z = zMin + epsilon;
        fixed = true;
        norm = glm::vec3(0.0, 0.0, 1.0);
    }
    if(this->pos.z > zMax) {
        this->pos.z = zMax - epsilon;
        fixed = true;
        norm = glm::vec3(0.0, 0.0, -1.0);
    }
    
    if(fixed) {
        this->velocity = glm::reflect(this->velocity, norm) * float(0.9);
    }
}

