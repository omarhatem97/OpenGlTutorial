#pragma once
class IndexBuffer
{
private:
    unsigned int m_rendererId;
    unsigned int m_cout;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return m_cout; }
};

