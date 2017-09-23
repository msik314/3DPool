#ifndef BOX_MESH_H
#define BOX_MESH_H

#include <gl/gl3w.h>

class BoxMesh
{
public:
    BoxMesh();

    ~BoxMesh();

    inline void draw()
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[1]);
        glDrawElements(GL_LINES, m_drawCount, GL_UNSIGNED_INT, NULL);
    }
private:
    GLuint m_vab[2];
    GLuint m_vao;

    GLuint m_drawCount;
};
#endif // BOX_MESH_H
