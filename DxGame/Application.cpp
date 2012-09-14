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
	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {

		}
	}
	return msg.wParam;
}

void Application::init(int width, int height) {
	window.setSize(width, height);
	window.create(WND_TITLE);
}