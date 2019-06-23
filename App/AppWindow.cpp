#include <stdexcept>
#include <GLFW/glfw3.h>
#include "AppWindow.h"


namespace app
{
	GLFWwindow* const createWindow()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		GLFWwindow* const window = glfwCreateWindow(800, 600, "My window", nullptr, nullptr);
		if (!window)
		{
			throw std::runtime_error("Unable to create application window!");
		}
		return window;
	}

	AppWindow::AppWindow() : window{ createWindow() }
	{
	}

	AppWindow::~AppWindow()
	{
		glfwDestroyWindow(window);
	}

	void AppWindow::makeContextCurrent() const
	{
		glfwMakeContextCurrent(window);
	}

	bool AppWindow::shouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void AppWindow::swapBuffers() const
	{
		glfwSwapBuffers(window);
	}
}