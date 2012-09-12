#include "stdafx.h"
#include "Application.h"

#include "Exception.h"

LPCTSTR Application::CLASS_NAME = TEXT("DxGame");
LPCTSTR Application::WND_TITLE = TEXT("Test");

Application::Application(HINSTANCE hInstance) : hInstance(hInstance), window(hInstance, CLASS_NAME) {
}

int Application::run() {
	init(640, 480);

	MSG msg;

	BOOL ret;
	while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (ret == -1)
			LOG(FATAL) << "GetMessage failed: " << Win32Error(GetLastError()).message();
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

void Application::init(int width, int height) {
	window.setSize(width, height);
	window.create(WND_TITLE);
}