#ifndef GLFW_WINDOW_HH
#define GLFW_WINDOW_HH

#include "Interface/Window/Window.hh"
#include <string>
#include <glfw/glfw3.h>

class GLFWWindow : public Window
{
public:
    GLFWWindow(uint32_t width, uint32_t height, std::string title);
    ~GLFWWindow();

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    virtual void Update() override;
    virtual std::any GetWindowPointer() override;
    virtual bool ShouldClose() const override;
private:
    void processInput();
    
    uint32_t m_Width;
    uint32_t m_Height;
    std::string m_Title;
    GLFWwindow* m_Window;
};

#endif
