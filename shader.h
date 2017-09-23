#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <gl/gl3w.h>

class Shader
{
public:
    Shader();

    ~Shader();

    inline void bind(){glUseProgram(m_program);}

    inline void updateMVP(const glm::mat4& mvp, uint8_t index){glUniformMatrix4fv(index, 1, false, &mvp[0][0]);}

    inline void updateColor(const glm::vec4& color, uint8_t index){glUniform4f(5 + index, color.x, color.y, color.z, color.w);}

private:
    GLuint m_program;
};

#endif // SHADER_H
