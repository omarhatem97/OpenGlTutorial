#include "IndexBuffer.h"
#include "Renderer.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_cout(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_rendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererId));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}