#include "GL4Context.hh"
#include <glad/gl_safe_include.h>
#include <iostream>
#include <cstdlib>

GL4Context::GL4Context(GLFWwindow* window) :
	m_Window(window)
{
	if (!gladLoadGL(glfwGetProcAddress))
	{
	    std::cout << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}
}

GL4Context::~GL4Context()
{
	gladLoaderUnloadGL();
}

void GL4Context::Clear()
{
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GL4Context::Present()
{
	glfwSwapBuffers(m_Window);
}

void GL4Context::SetClearColor(float r, float g, float b, float a)
{
	m_ClearColor[0] = r;
	m_ClearColor[1] = g;
	m_ClearColor[2] = b;
	m_ClearColor[3] = a;
}
