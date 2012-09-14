#include "stdafx.h"
#include "Application.h"

#include "Exception.h"

#undef _WINGDI_			// workaround for bug in atlconv.h when we define NOGDI 
#include <atlconv.h>

static const char* getArg0() {
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	USES_CONVERSION;
	LPCSTR arg0 = W2A(argv[0]);
	LocalFree(argv);
	if (!arg0)
		throw std::runtime_error("W2A failed");

	static char ret[100];
	strncpy_s(ret, arg0, 100);
	return ret;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, int nShowCmd)
{
	google::InitGoogleLogging(getArg0());

	try {
		Application app(hInstance);

		return app.run();
	} catch (Exception& e) {
		LOG(FATAL) << "Unhandled Exception: " << e;
		return 1;
	}
}