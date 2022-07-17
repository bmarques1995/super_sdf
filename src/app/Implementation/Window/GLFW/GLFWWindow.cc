#include "GLFWWindow.hh"
#include <iostream>
#include <cstdlib>

GLFWWindow::GLFWWindow(uint32_t width, uint32_t height, std::string title):
	m_Width(width), m_Height(height), m_Title(title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
	
	});
}

GLFWWindow::~GLFWWindow()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

uint32_t GLFWWindow::GetWidth() const
{
	return m_Width;
}

uint32_t GLFWWindow::GetHeight() const
{
	return m_Height;
}

void GLFWWindow::Update()
{
	processInput();
	glfwPollEvents();
}

std::any GLFWWindow::GetWindowPointer()
{
	return m_Window;
}

bool GLFWWindow::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

void GLFWWindow::processInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);
}
