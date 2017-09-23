#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include "audio.h"

inline void checkCollision(Ball& b1, uint8_t b1Index, Ball& b2, uint8_t b2Index, glm::vec3* positions, glm::vec3* velocity, uint8_t* numCollisions, char* sound)
{
    glm::vec3 p1 = b1.getTransform().getPos();
    glm::vec3 p2 = b2.getTransform().getPos();
    glm::vec3 diff = p2 - p1;
    float r1 = b1.getRadius();
    float r2 = b2.getRadius();
    float rSquared = (r1 + r2) * (r1 + r2);
    if(glm::dot(diff, diff) <= rSquared)
    {
        glm::vec3 v1 = b1.getVelocity();
        glm::vec3 v2 = b2.getVelocity();
        glm::vec3 v1Res;
        glm::vec3 v2Res;
        positions[b1Index] += p1 + diff/2.0f - r1 * glm::normalize(diff);
        positions[b2Index] += p1 + diff/2.0f + r2 * glm::normalize(diff);
        diff = positions[b2Index] - positions[b1Index];
        v1Res = v1 - -diff * glm::dot(v1 - v2, -diff)/glm::length2(diff);
        v2Res = v2 - diff * glm::dot(v2 - v1, diff)/glm::length2(diff);
        velocity[b1Index] += v1Res;
        velocity[b2Index] += v2Res;
        ++numCollisions[b1Index];
        ++numCollisions[b2Index];
        if(sound) playSound(sound);
    }
}

inline void physicsFrame(double delta, Ball* balls, glm::vec3* positions, glm::vec3* velocity, uint8_t* numCollisions,
                         uint8_t numBalls, float boxDimension, char* colSound = NULL, char* wallSound = NULL)
{
    const float FRICTION = 0.4;
    const float CUTOFF = 0.05;

    /*for(uint8_t i = 0; i < numBalls; ++i)
    {
        if(!balls[i].getActive())continue;
        balls[i].fixedUpdate();
    }*/

    for(uint8_t i = 0; i < numBalls; ++i)
    {
        //if(!balls[i].getActive())continue;
        if(glm::length2(balls[i].getVelocity()) >= CUTOFF * CUTOFF)
        {
            glm::vec3 acc = -glm::normalize(balls[i].getVelocity()) * FRICTION;
            balls[i].getTransform().getPos() += balls[i].getVelocity() * float(delta) + 0.5f * acc * float(delta) * float(delta);
            balls[i].getVelocity() += acc * float(delta);
        }
    }

    for(uint8_t i = 1; i < numBalls; ++i)
    {
        //if(!balls[i].getActive())continue;
        for(uint8_t j = 0; j < i; ++j)
        {
            //if(!balls[j].getActive())continue;
            checkCollision(balls[i], i, balls[j], j, positions, velocity, numCollisions, colSound);
        }
    }

    for(uint8_t i = 0; i < numBalls; ++i)
    {
        //if(!balls[i].getActive()) continue;
        if(numCollisions[i])
        {
            balls[i].getVelocity() = velocity[i] / float(numCollisions[i]);
            balls[i].getTransform().getPos() = positions[i]/float(numCollisions[i]);
            velocity[i] = glm::vec3();
            positions[i] = glm::vec3();
            numCollisions[i] = 0;
        }
        if(balls[i].getTransform().getPos().x + balls[i].getRadius() >= boxDimension)
        {
            balls[i].getVelocity().x  =- glm::abs(balls[i].getVelocity().x);
            if(wallSound) playSound(wallSound);
        }
        else if(balls[i].getTransform().getPos().x - balls[i].getRadius() <= -boxDimension)
        {
            balls[i].getVelocity().x  = glm::abs(balls[i].getVelocity().x);
            if(wallSound) playSound(wallSound);
        }

        if(balls[i].getTransform().getPos().y + balls[i].getRadius() >= boxDimension)
        {
            balls[i].getVelocity().y  =- glm::abs(balls[i].getVelocity().y);
            if(wallSound) playSound(wallSound);
        }
        else if(balls[i].getTransform().getPos().y - balls[i].getRadius() <= -boxDimension)
        {
            balls[i].getVelocity().y  = glm::abs(balls[i].getVelocity().y);
            if(wallSound) playSound(wallSound);
        }

        if(balls[i].getTransform().getPos().z + balls[i].getRadius() >= boxDimension)
        {
            balls[i].getVelocity().z  =- glm::abs(balls[i].getVelocity().z);
            if(wallSound) playSound(wallSound);
        }
        else if(balls[i].getTransform().getPos().z - balls[i].getRadius() <= -boxDimension)
        {
            balls[i].getVelocity().z  = glm::abs(balls[i].getVelocity().z);
            if(wallSound) playSound(wallSound);
        }
    }
}

#endif // PHYSICS_H
