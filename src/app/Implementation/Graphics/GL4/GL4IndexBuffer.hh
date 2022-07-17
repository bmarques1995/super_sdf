#ifndef GL4_INDEX_BUFFER_HH
#define GL4_INDEX_BUFFER_HH

#include <cstdint>
#include "Interface/Graphics/IndexBuffer.hh"

class GL4IndexBuffer : public IndexBuffer
{
public:
	GL4IndexBuffer(const void* data, size_t size);
	~GL4IndexBuffer();

	virtual void Bind() const override;
private:
	uint32_t m_ElementID;
};


#endif
