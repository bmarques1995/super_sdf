#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <cstdint>

enum class TextureFilter
{
    Linear = 0,
    Nearest,
};

class Texture
{
public:
    virtual void Bind(uint32_t slot = 0) const = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
};

#endif // !1
