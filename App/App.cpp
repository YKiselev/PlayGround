#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include "AppWindow.h"

void errorCallback(int error, const char* description)
{
	std::cout << "ERROR(" << error << ", \"" << description << "\"" << std::endl;
}

int main()
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		return 1;
	}

	{
		const app::AppWindow window;

		window.makeContextCurrent();
		glfwSwapInterval(1);

		const std::chrono::milliseconds timespan(5);
		while (!window.shouldClose())
		{
			glfwPollEvents();
			window.swapBuffers();
			std::this_thread::sleep_for(timespan);
		}
	}
	
	glfwTerminate();

	return 0;
}
