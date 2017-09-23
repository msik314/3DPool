#ifndef BALL_H
#define BALL_H

#include "transform.h"

class Ball
{
public:
    Ball(float radius, const Transform& transform = Transform(), const glm::vec4& color = glm::vec4(1, 1, 1, 1)):
        m_radius(radius), m_transform(transform), m_color(color), m_active(true), m_velocity(glm::vec3()){}

    void input(){}

    //inline void update(double delta){}

    //inline void fixedUpdate(double FixedDelta){}

    inline void onPocket(){m_active = false;}

    inline Transform& getTransform() {return m_transform;}
    inline const Transform& getTransform() const {return m_transform;}

    inline glm::vec4& getColor() {return m_color;}
    inline const glm::vec4& getColor() const {return m_color;}

    inline glm::vec3& getVelocity() {return m_velocity;}

    //inline bool getActive() const {return m_active;}
    //inline void setActive(bool active) {m_active = active;}

    inline float getRadius() const {return m_radius;}

private:
    float m_radius;
    Transform m_transform;
    glm::vec4 m_color;
    glm::vec3 m_velocity;
    bool m_active;
};

#endif // BALL_H
