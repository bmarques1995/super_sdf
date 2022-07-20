#ifndef GL4_INPUT_LAYOUT_HH
#define GL4_INPUT_LAYOUT_HH

#include "Interface/Graphics/InputLayout.hh"
#include <glad/gl_safe_include.h>

class GL4InputLayout : public InputLayout
{
public:
	GL4InputLayout(const std::initializer_list<BufferElement>& elementList);
	~GL4InputLayout();

	virtual void Bind() const override;
private:
	GLenum GetFormat(ShaderDataType type);

	uint32_t m_ElementID;
	BufferLayout m_Layout;
};

#endif
