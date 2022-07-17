#ifndef GL4_TEXTURE_HH
#define GL4_TEXTURE_HH

#include "Interface/Graphics/Texture.hh"
#include "wrappers/Image.hh"
#include <glad/gl_safe_include.h>

class GL4Texture : public Texture 
{
public:
    GL4Texture(const Image& image, TextureFilter filter = TextureFilter::Linear);
    ~GL4Texture();
	virtual void Bind(uint32_t slot = 0) const override;
    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;
private:
    GLint GetNativeMagFilver(TextureFilter filter);
    GLint GetNativeMinFilver(TextureFilter filter);
    uint32_t m_TextureID;
    uint32_t m_Width;
    uint32_t m_Height;
};

#endif