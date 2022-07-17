#include "GL4VertexBuffer.hh"
#include <glad/gl_safe_include.h>

GL4VertexBuffer::GL4VertexBuffer(const void* data, size_t size)
{
	glGenBuffers(1, &m_ElementID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ElementID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GL4VertexBuffer::~GL4VertexBuffer()
{
	glDeleteBuffers(1, &m_ElementID);
}

void GL4VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ElementID);
}
