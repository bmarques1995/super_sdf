#ifndef GL4_CONTEXT_HH
#define GL4_CONTEXT_HH

#include "Interface/Graphics/Context.hh"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#undef GLFW_INCLUDE_NONE

class GL4Context : public Context
{
public:
	GL4Context(GLFWwindow* window);
	~GL4Context();
	virtual void Clear() override;
	virtual void Present() override;
	virtual void SetClearColor(float r, float g, float b, float a = 1.0f) override;
private:
	GLFWwindow* m_Window;
	float m_ClearColor[4] = {.0f, .0f, .0f, 1.0f};
};

#endif
