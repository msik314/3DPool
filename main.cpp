#define GLM_FORCE_RADIANS
#include "window.h"
#include "shader.h"
#include "sphereMesh.h"
#include "boxMesh.h"
#include "transform.h"
#include "camera.h"
#include "ball.h"
#include "physics.h"
#include "audio.h"

#ifdef DEBUG
#include <cstdio>
#endif // DEBUG

inline float constrain(float min, float max, float value)
{
    return value < min ? min: (value > max ? max : value);
}

inline void reset(Ball* balls)
{
    const float M_SCALE = float(1/0.85065081);
    glm::vec3 ballPoses[] = {glm::vec3(),
                             glm::vec3(-1.0001, -0.5774, -1.6330),
                             glm::vec3(1.0001, -0.5774, -1.6330),
                             glm::vec3(0, 1.1548, -1.6330)};
    glm::vec4 colors[] = {glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
                          glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                          glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                          glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)};

    balls[0] = Ball(1, Transform(glm::vec3(0, 0, 2.5), glm::quat(), glm::vec3(M_SCALE, M_SCALE, M_SCALE)));
    balls[0].getVelocity() = glm::vec3(0, 0, 0);
    for(uint8_t i = 0; i < 4; ++i)
    {
        balls[i + 1] = Ball(1, Transform(ballPoses[i], glm::quat(), glm::vec3(M_SCALE, M_SCALE, M_SCALE)), colors[i]);
        balls[i + 1].getVelocity() = glm::vec3();
    }
}

int main()
{
    const float M_SCALE = float(1/0.85065081);
    const float SENSITIVITY = 0.005f;
    const float CUTOFF = 0.05;

    uint8_t* pool = new uint8_t[5 * (sizeof(Ball) + 2 * sizeof(glm::vec3) + 1)];
    Ball* balls = (Ball*)pool;
    glm::vec3* positions = (glm::vec3*)(pool + 5 * sizeof(Ball));
    glm::vec3* velocities = (glm::vec3*)(pool + 5 * (sizeof(Ball) + sizeof(glm::vec3)));

    uint8_t* numCollisions = pool + 5 * (sizeof(Ball) + 2 * sizeof(glm::vec3));

    #ifdef DEBUG
    Window window(1280, 720, "3DPool");
    #else
    Window window(1920, 1080, "3DPool", true);
    #endif // DEBUG

    Shader shader;
    SphereMesh sphere;
    BoxMesh box;

    Camera cam(Transform(glm::vec3(0,0,7.5)));

    glm::vec3 ballPoses[] = {glm::vec3(),
                             glm::vec3(-1.0001, -0.5774, -1.6330),
                             glm::vec3(1.0001, -0.5774, -1.6330),
                             glm::vec3(0, 1.1548, -1.6330)};

    glm::vec4 colors[] = {glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
                          glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                          glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                          glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)};
    shader.bind();

    balls[0] = Ball(1, Transform(glm::vec3(0, 0, 2.5), glm::quat(), glm::vec3(M_SCALE, M_SCALE, M_SCALE)));
    balls[0].getVelocity() = glm::vec3(0, 0, 0);
    shader.updateColor(balls[0].getColor(), 0);
    for(uint8_t i = 0; i < 4; ++i)
    {
        balls[i + 1] = Ball(1, Transform(ballPoses[i], glm::quat(), glm::vec3(M_SCALE, M_SCALE, M_SCALE)), colors[i]);
        shader.updateColor(balls[i + 1].getColor(), i + 1);
    }

    glm::dvec2 cursorPos;
    glfwGetCursorPos(window.GetWindow(), &cursorPos.x, &cursorPos.y);

    float chargePower = 0;
    glm::vec3 focus;

    double time = 0;
    double delta = 1.0f/60;
    glfwSetTime(0);
    while(!glfwWindowShouldClose(window.GetWindow()))
    {
        while(glfwGetTime() - time  < 1.0/60){}
        delta = glfwGetTime() - time;
        time += delta;

        window.pollEvents();
        if(glfwGetKey(window.GetWindow(),GLFW_KEY_ESCAPE))window.close();
        else if(glfwGetKey(window.GetWindow(), GLFW_KEY_SPACE))reset(balls);

        if(glm::length2(balls[0].getVelocity()) < CUTOFF * CUTOFF)
        {
            if(glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
            {
                chargePower = constrain(0, 1, chargePower + 1.0f/60);
                balls[0].getColor() = glm::vec4(1.0f, 1 - chargePower, 1 - chargePower, 1.0f);
            }

            else
            {
                balls[0].getVelocity() = cam.getTransform().getRot() * glm::vec3(0,0,-chargePower * 6);
                if(chargePower >= CUTOFF)playSound("Collision16.wav");
            }

            focus = balls[0].getTransform().getPos();
        }
        else
        {
            chargePower = 0;
            balls[0].getColor() = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }

        glfwGetCursorPos(window.GetWindow(), &cursorPos.x, &cursorPos.y);

        cursorPos.y = constrain((-glm::half_pi<float>() + 0.1f)/SENSITIVITY, (glm::half_pi<float>() - 0.1f)/SENSITIVITY, float(cursorPos.y));
        glfwSetCursorPos(window.GetWindow(), cursorPos.x, cursorPos.y);

        cam.getTransform().getRot() = glm::angleAxis(-SENSITIVITY * float(cursorPos.x), glm::vec3(0,1,0));
        cam.getTransform().getRot() *= glm::angleAxis(-SENSITIVITY * float(cursorPos.y), glm::vec3(1,0,0));
        cam.getTransform().getPos() = focus + cam.getTransform().getRot() * glm::vec3(0,0,5);

        physicsFrame(delta, balls, positions, velocities, numCollisions, 5, 4, "Collision16.wav", "Thud16.wav");

        window.clear(0,0,0,1);

        shader.updateColor(balls[0].getColor(), 0);

        for(int i = 0; i < 5; ++i)
        {
            shader.updateMVP(cam.getVP() * balls[i].getTransform().getModel(), i);
        }
        sphere.draw(5);

        shader.updateColor(colors[2], 0);
        shader.updateMVP(cam.getVP(), 0);
        box.draw();

        window.swapBuffers();
        #ifdef DEBUG
        printf("%.5f\n", delta);
        #endif // DEBUG
    }

    delete[] pool;
    return 0;
}
