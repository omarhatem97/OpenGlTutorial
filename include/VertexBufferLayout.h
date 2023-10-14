#pragma once

#include <vector>

#include "glad/glad.h"
#include "Renderer.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type)
        {
        case GL_FLOAT: return 4; break;
        case GL_UNSIGNED_INT: return 5; break;
        case GL_UNSIGNED_BYTE: return 1; break;
        }
        ASSERT(false)
        return 0;
    }
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_stride;

public:
    VertexBufferLayout()
    :m_stride(0)
    {}

    ~VertexBufferLayout() {}

    template<typename T>
    void push(unsigned int count) {
        static_assert(false);
    }

    template<>
    void push<float>(unsigned int count) {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE});
        m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    void push<unsigned int>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE});
        m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE});
        m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }
    inline const unsigned int getStride() const { return m_stride; }

};
