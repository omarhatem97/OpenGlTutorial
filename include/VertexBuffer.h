#pragma once
class VertexBuffer
{
private:
    unsigned int m_rendererId;
public:
    VertexBuffer(void * data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

