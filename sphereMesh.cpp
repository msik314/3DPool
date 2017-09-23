#include "sphereMesh.h"
#include "sphereMeshData.hpp"

SphereMesh::SphereMesh()
{
    m_drawCount = SphereMeshData::numIndices;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(2, m_vab);
    glBindBuffer(GL_ARRAY_BUFFER, m_vab[0]);
    glBufferData(GL_ARRAY_BUFFER, SphereMeshData::numVertices * sizeof(glm::vec3), SphereMeshData::vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, SphereMeshData::numIndices * sizeof(uint32_t), SphereMeshData::indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

SphereMesh::~SphereMesh()
{
    glDeleteBuffers(2, m_vab);
    glDeleteVertexArrays(1, &m_vao);
}
