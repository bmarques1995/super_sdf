#include "GL4IndexBuffer.hh"
#include <glad/gl_safe_include.h>

GL4IndexBuffer::GL4IndexBuffer(const void* data, size_t size)
{
	glGenBuffers(1, &m_ElementID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GL4IndexBuffer::~GL4IndexBuffer()
{
	glDeleteBuffers(1, &m_ElementID);
}

void GL4IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementID);
}
