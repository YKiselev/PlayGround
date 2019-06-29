#include <stdexcept>
#include <GLFW/glfw3.h>
#include "AppWindow.h"


namespace app
{
	AppWindow::AppWindow(GLFWwindow* wnd) : window{ wnd }
	{
	}

	//AppWindow::AppWindow(const char* title, const Size& size, const ContextVersion& contextVersion, bool fullScreen)
	//{
	//	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, std::get<0>(contextVersion));
	//	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, std::get<1>(contextVersion));
	//	window = ::glfwCreateWindow(std::get<0>(size), std::get<1>(size), title, nullptr, nullptr);
	//	if (!window)
	//	{
	//		throw std::runtime_error("Unable to create application window!");
	//	}
	//}

	AppWindow::AppWindow(AppWindow&& src) noexcept : window{ src.window }
	{
		src.window = nullptr;
	}

	AppWindow::~AppWindow()
	{
		::glfwDestroyWindow(window);
		window = nullptr;
	}

	void AppWindow::makeContextCurrent() const
	{
		::glfwMakeContextCurrent(window);
	}

	bool AppWindow::shouldClose() const
	{
		return ::glfwWindowShouldClose(window);
	}

	void AppWindow::swapBuffers() const
	{
		::glfwSwapBuffers(window);
	}

	AppWindow& AppWindow::operator = (AppWindow&& src) noexcept
	{
		window = src.window;
		src.window = nullptr;
		return *this;
	}

	AppWindow AppWindow::Builder::build()
	{
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		GLFWwindow* window = ::glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window)
		{
			throw std::runtime_error("Unable to create application window!");
		}
		return AppWindow(window);
	}
}