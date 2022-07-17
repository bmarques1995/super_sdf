#include "GL4InputLayout.hh"

GL4InputLayout::GL4InputLayout(const std::initializer_list<BufferElement>& elementList) :
	m_Layout(elementList)
{
	glGenVertexArrays(1, &m_ElementID);
	glBindVertexArray(m_ElementID);

	auto elements = m_Layout.GetElements();

	for (size_t i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer
		(
			(uint32_t) i,
			elements[i].GetElementCount(),
			GetFormat(elements[i].Type),
			elements[i].Normalized ? GL_TRUE : GL_FALSE,
			m_Layout.GetStride(),
			(void*)elements[i].Offset
		);
	}
}

GL4InputLayout::~GL4InputLayout()
{
	glDeleteVertexArrays(1, &m_ElementID);
}

void GL4InputLayout::Bind() const
{
	glBindVertexArray(m_ElementID);
}

GLenum GL4InputLayout::GetFormat(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:
	case ShaderDataType::Float2:
	case ShaderDataType::Float3:
	case ShaderDataType::Float4:
		return GL_FLOAT;
	case ShaderDataType::Uint:
	case ShaderDataType::Uint2:
	case ShaderDataType::Uint3:
	case ShaderDataType::Uint4:
		return GL_UNSIGNED_INT;
	case ShaderDataType::Bool:
		return GL_BOOL;
	default:
		return GL_FALSE;
	}
}
