#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include <gl/gl3w.h>

class SphereMesh
{
public:
    SphereMesh();

    ~SphereMesh();

    inline void draw(uint32_t instances)
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[1]);
        glDrawElementsInstanced(GL_LINES, m_drawCount, GL_UNSIGNED_INT, NULL, instances);
    }
private:
    GLuint m_vab[2];
    GLuint m_vao;

    GLuint m_drawCount;
};

#endif // SPHERE_MESH_H
