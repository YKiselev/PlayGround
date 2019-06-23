#pragma once

#include <stdexcept>
#include <GLFW/glfw3.h>

namespace app
{
	class AppWindow
	{
	public:
		AppWindow();
		~AppWindow();

		void makeContextCurrent() const;
		bool shouldClose() const;
		void swapBuffers() const;

	private:
		GLFWwindow* const window;
	};
}