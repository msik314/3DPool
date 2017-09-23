#include "window.h"

Window::Window(uint32_t width, uint32_t height, const char* title, bool fullScreen):
    m_width(width), m_height(height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    m_window = glfwCreateWindow(1280, 720, "3D Pool", (GLFWmonitor*)(fullScreen * uint64_t(glfwGetPrimaryMonitor())), NULL);
    glfwMakeContextCurrent(m_window);

    gl3wInit();
    glViewport(0, 0, 1280, 720);
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(m_window, 0, 0);
}
