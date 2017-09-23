#ifndef WINDOW_H
#define WINDOW_H

#include <gl/gl3w.h>
#include <glfw/glfw3.h>

class Window
{
public:
    Window(uint32_t width, uint32_t height, const char* title, bool fullScreen = false);

    ~Window(){glfwTerminate();}

    inline void clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    inline void swapBuffers(){glfwSwapBuffers(m_window);}

    inline void pollEvents(){glfwPollEvents();}

    inline void close(){glfwSetWindowShouldClose(m_window, true);}

    inline GLFWwindow* GetWindow() const {return m_window;}

    inline uint32_t getWidth(){}
    inline uint32_t getHeight(){}
private:
    GLFWwindow* m_window;
    uint32_t m_width;
    uint32_t m_height;
};
#endif // WINDOW_H
