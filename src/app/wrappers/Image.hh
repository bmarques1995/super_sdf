#ifndef IMAGE_HH
#define IMAGE_HH

#include <string>
#include <stb_image.h>
#include <cstdint>

class Image
{
public:
	Image(std::string_view filepath, uint32_t desiredChannels = 4);
	~Image();

	uint8_t* GetBuffer() const;
	
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	uint32_t GetChannels() const;

	bool IsValid() const;

private:
	unsigned char* m_Buffer;
	bool m_FromFile;

	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_Channels;
};

#endif // !1
