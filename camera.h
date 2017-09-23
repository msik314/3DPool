#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include "transform.h"

class Camera
{
public:
    Camera(const Transform& transform = Transform(), float fovy = glm::radians(70.0f), float aspect = 16.0f/9.0f, float near = 0.1f, float far = 1000.0f)
    {
        m_transform = transform;
        m_projection = glm::perspective(fovy, aspect, 0.1f, 1000.0f);
    }

    inline void lookAt(glm::vec3 point)
    {
        glm::vec3 up = glm::vec3(0,1,0);
        glm::vec3 forward = glm::normalize(point - m_transform.getPos());
        float dot = glm::dot(forward, up);
        if (dot >=.99999)
        {
            m_transform.getRot() = glm::angleAxis(glm::half_pi<float>(), glm::vec3(1, 0, 0));
            return;
        }
        else if (dot <= -.99999)
        {
            m_transform.getRot() = glm::angleAxis(glm::half_pi<float>(), glm::vec3(-1, 0, 0));
            return;
        }
        //Vector::OrthoNormalize(&up, &forward); // Keeps up the same, make forward orthogonal to up

        glm::vec3 right = glm::cross(up, forward);

        glm::quat ret;
        ret.w = glm::sqrt(1.0f + right.x + up.y + forward.z) * 0.5f;
        float w4_recip = 1.0f / (4.0f * ret.w);
        ret.x = (forward.y - up.z) * w4_recip;
        ret.y = (right.z - forward.x) * w4_recip;
        ret.z = (up.x - right.y) * w4_recip;

        m_transform.getRot() = ret;
    }

    inline glm::mat4 getVP() const {return m_projection * glm::inverse(m_transform.getModel());}

    inline Transform& getTransform() {return m_transform;}
    inline const  Transform& getTransform() const {return m_transform;}

private:
    Transform m_transform;
    glm::mat4 m_projection;
};

#endif // CAMERA_H
