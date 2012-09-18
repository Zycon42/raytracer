#include "stdafx.h"
#include "Window.h"

#include "Exception.h"

Window::Window(HINSTANCE hInstance, LPCTSTR className) 
	: hWnd(0), className(className), hInstance(hInstance), rect(0, 0, 640, 480) {

	WNDCLASSEX cls;
	ZeroMemory(&cls, sizeof(cls));
	cls.cbSize = sizeof(cls);
	cls.hInstance = hInstance;
	cls.lpszClassName = className;
	cls.style = CS_HREDRAW | CS_VREDRAW;
	cls.hCursor = LoadCursor(NULL, IDC_ARROW);
	cls.hbrBackground = (HBRUSH)COLOR_WINDOW;
	cls.lpfnWndProc = staticWndProc;

	if (!RegisterClassEx(&cls))
		throw Win32Exception("RegisterClassEx failed");
}

Window::~Window(void) {
	if (hWnd != 0) {
		DestroyWindow(hWnd);
		hWnd = 0;
	}
}

void Window::create(LPCTSTR title) {
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD exStyle = WS_EX_APPWINDOW;

	RECT rect = this->rect;
	AdjustWindowRectEx(&rect, style, FALSE, exStyle);
	// fix negative values
	if (rect.left < 0) {
		rect.right -= rect.left;
		rect.left = 0;
	}
	if (rect.top < 0) {
		rect.bottom -= rect.top;
		rect.top = 0;
	}

	hWnd = CreateWindowEx(exStyle, 
		className, 
		title, style, 
		rect.left, rect.top, 
		rect.right - rect.left, rect.bottom - rect.top, 
		0, 0, 
		hInstance, 
		this);
	if (!hWnd)
		throw Win32Exception("CreateWindowEx failed");

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
}

LRESULT Window::staticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LONG_PTR userData = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (!userData) {
		if (uMsg == WM_CREATE) {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(cs->lpCreateParams));
			return 0;
		}
	} else {
		Window* wnd = reinterpret_cast<Window*>(userData);
		return wnd->handleMessage(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_MOVE:
		setPos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}