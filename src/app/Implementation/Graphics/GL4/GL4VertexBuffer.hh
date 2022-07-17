#ifndef GL4_VERTEX_BUFFER_HH
#define GL4_VERTEX_BUFFER_HH

#include <cstdint>
#include "Interface/Graphics/VertexBuffer.hh"

class GL4VertexBuffer : public VertexBuffer
{
public:
	GL4VertexBuffer(const void* data, size_t size);
	~GL4VertexBuffer();

	virtual void Bind() const override;
private:
	uint32_t m_ElementID;
};


#endif // !1
