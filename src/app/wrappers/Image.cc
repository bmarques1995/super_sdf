#include "Image.hh"

Image::Image(std::string_view filepath, uint32_t desiredChannels)
{
    int width, height, nrChannels;
    m_Buffer = stbi_load(filepath.data(), &width, &height, &nrChannels, desiredChannels);
    m_Width = width > 0 ? width : 0;
    m_Height = height > 0 ? height : 0;
    m_Channels = desiredChannels;
    m_FromFile = true;
}

Image::Image(uint8_t** buffer, uint32_t width, uint32_t height, uint32_t numberOfChannels)
{
    m_Buffer = *buffer;
    m_Width = width;
    m_Height = height;
    m_Channels = numberOfChannels;
    m_FromFile = true;
}

Image::~Image()
{
    if(m_FromFile)
        stbi_image_free(m_Buffer);
}

unsigned char* Image::GetBuffer() const
{
    return m_Buffer;
}

uint32_t Image::GetWidth() const
{
    return m_Width;
}

uint32_t Image::GetHeight() const
{
    return m_Height;
}

uint32_t Image::GetChannels() const
{
    return m_Channels;
}

bool Image::IsValid() const
{
    return ((m_Width > 0) && (m_Height > 0) && (m_Channels > 0));
}
