#pragma once

#include <stdexcept>
#include <GLFW/glfw3.h>

namespace app
{
	class AppWindow
	{
	public:
		class Builder;

		AppWindow(GLFWwindow *wnd);
		AppWindow(const AppWindow& src) = delete;
		AppWindow(AppWindow&& src) noexcept;
		~AppWindow();

		void makeContextCurrent() const;
		bool shouldClose() const;
		void swapBuffers() const;

		AppWindow& operator = (const AppWindow& src) = delete;
		AppWindow& operator = (AppWindow&& src) noexcept;

	private:
		GLFWwindow* window;
	};


	class AppWindow::Builder
	{
	public:
		Builder& withTitle(const char* value)
		{
			title = value;
			return *this;
		}

		Builder& withSize(int w, int h)
		{
			width = w;
			height = h;
			return *this;
		}

		Builder& withContextVersion(int major, int minor)
		{
			majorVersion = major;
			minorVersion = minor;
			return *this;
		}

		Builder& withFullScreen(bool value)
		{
			fullScreen = value;
			return *this;
		}

		AppWindow build();

	private:
		const char* title{ "Playground" };
		int width{ 800 }, height{ 600 };
		int majorVersion{ 4 }, minorVersion{ 0 };
		bool fullScreen{ false };
	};
}