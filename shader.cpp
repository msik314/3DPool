#include "shader.h"
#include <cstring>

#ifdef DEBUG
#include <cstdio>
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram);
#endif // DEBUG

Shader::Shader()
{
    const char* vertSrc = "#version 430\n"
                    "layout(location = 0)in vec3 position;"
                    "layout(location = 0)out vec4 color;"
                    "layout(location = 0)uniform mat4 mvps[5];"
                    "layout(location = 5)uniform vec4 colors[5];"
                    "void main()"
                    "{"
                        "color = colors[gl_InstanceID];"
                        "gl_Position = mvps[gl_InstanceID] * vec4(position, 1.0f);"
                    "}" ;
    const int vertLen = strlen(vertSrc);

    const char* fragSrc = "#version 430\n"
                    "layout(location = 0)in vec4 color;"
                    "layout(location = 0)out vec4 outColor;"
                    "void main()"
                    "{"
                        "outColor = color;"
                    "}";
    const int fragLen = strlen(fragSrc);

    m_program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, &vertLen);
    glCompileShader(vertexShader);
    #ifdef DEBUG
    checkShaderError(vertexShader, GL_COMPILE_STATUS, false);
    #endif // DEBUG

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, &fragLen);
    glCompileShader(fragmentShader);
    #ifdef DEBUG
    checkShaderError(fragmentShader, GL_COMPILE_STATUS, false);
    #endif // DEBUG

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    glLinkProgram(m_program);
    glValidateProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}
#ifdef DEBUG
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		printf("%s\n", error);
	}
}
#endif // DEBUG
