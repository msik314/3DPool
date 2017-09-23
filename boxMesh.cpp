#include "boxMesh.h"

#include <glm/glm.hpp>

BoxMesh::BoxMesh()
{
    glm::vec3 vertices[] = {glm::vec3(-4, -4, -4),
                            glm::vec3(-4, -4, 4),
                            glm::vec3(-4, 4, -4),
                            glm::vec3(-4, 4, 4),
                            glm::vec3(4, -4, -4),
                            glm::vec3(4, -4, 4),
                            glm::vec3(4, 4, -4),
                            glm::vec3(4, 4, 4)};
    uint32_t indices[] = {0, 1, 1, 3, 2, 3, 2, 0,
                          4, 5, 5, 7, 6, 7, 6, 4,
                          0, 4, 1, 5, 2, 6, 3, 7};
    m_drawCount = 24;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(2, m_vab);
    glBindBuffer(GL_ARRAY_BUFFER, m_vab[0]);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

BoxMesh::~BoxMesh()
{
    glDeleteBuffers(2, m_vab);
    glDeleteVertexArrays(1, &m_vao);
}
