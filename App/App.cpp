#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <ScopeGuard.h>
#include <windows.h>
#include "AppWindow.h"


void errorCallback(int error, const char* description)
{
	std::cout << "ERROR(" << error << ", \"" << description << "\"" << std::endl;
}

int offset = 0;
RECT r{ 0, 0, 100, 100 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
		SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

		//MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

		//wglDeleteContext(ourOpenGLRenderingContext);
		//PostQuitMessage(0);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		FillRect(hdc, &r, (HBRUSH)(COLOR_BACKGROUND));

		EndPaint(hWnd, &ps);
	}
	return 0;

	case WM_CLOSE:
		//if (MessageBox(hWnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
	{
		DestroyWindow(hWnd);
	}
	// Else: User canceled. Do nothing.
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;

}

int main()
{
	MSG msg = { 0 };
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = nullptr;
	wc.hbrBackground = (HBRUSH) nullptr;// (COLOR_BACKGROUND);
	wc.lpszClassName = L"Playground";
	wc.style = CS_OWNDC;
	if (!RegisterClass(&wc))
	{
		return 1;
	}
	HWND hWnd = CreateWindowW(wc.lpszClassName, L"openglversioncheck", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480, 0, 0, nullptr, 0);

	while (true)//GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		offset++;// 
		int delta = offset % 100;

		//r.left += offset;
		r.right += delta;
		
		InvalidateRect(hWnd, nullptr, TRUE);
	}

	/*
	::glfwSetErrorCallback(errorCallback);

	if (!::glfwInit())
	{
		return 1;
	}
	const pg::commons::OnScopeExit terminator{ ::glfwTerminate };

	const app::AppWindow window = app::AppWindow::Builder{}.build();

	window.makeContextCurrent();
	::glfwSwapInterval(1);

	const std::chrono::milliseconds timespan(5);
	while (!window.shouldClose())
	{
		::glfwPollEvents();
		window.swapBuffers();
		std::this_thread::sleep_for(timespan);
	}
	*/
	return 0;
}
