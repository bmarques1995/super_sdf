#ifndef WINDOW_HH
#define WINDOW_HH

#include <any>
#include <cstdint>

class Window
{
public:
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void Update() = 0;
    virtual std::any GetWindowPointer() = 0;
    virtual bool ShouldClose() const = 0;
};

#endif // !1
