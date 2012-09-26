#include "SymHandler.h"

#include "Exception.h"
#include "common.h"

// without NOGDI there's name conflict with glog (windows define ERROR macro)
#define NOGDI
#include <Windows.h>

#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp")

SymHandler& SymHandler::instance() {
	static SymHandler inst;
	return inst;
}

SymHandler::SymHandler() : isInitialized(false) {
	if (SymInitialize(GetCurrentProcess(), nullptr, TRUE) == FALSE) {
		throw Win32Exception("SymHandler::SymHandler: SymInitialize() failed", GetLastError(), false);
	}

	isInitialized = true;
}

SymHandler::~SymHandler() {
	if (isInitialized)
		SymCleanup(GetCurrentProcess());
}

void SymHandler::captureStackTrace(std::vector<uint64_t>& framePtrs, size_t skip, CONTEXT* context) {
	if (!isInitialized)
		throw std::logic_error("SymHandler is not initialized");

	// get context if we don't have it
	CONTEXT currentContext;
	if (!context) {
		RtlCaptureContext(&currentContext);
		context = &currentContext;
	}

	// init STACKFRAME
	STACKFRAME64 frame;
	ZeroMemory(&frame, sizeof(frame));
	DWORD machineType;
#ifdef _M_IX86
	machineType = IMAGE_FILE_MACHINE_I386;
	frame.AddrPC.Offset = context->Eip;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = context->Ebp;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrStack.Offset = context->Esp;
	frame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	machineType = IMAGE_FILE_MACHINE_AMD64;
	frame.AddrPC.Offset = context->Rip;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = context->Rdi;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrStack.Offset = context->Rsp;
	frame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	machineType = IMAGE_FILE_MACHINE_IA64;
	frame.AddrPC.Offset = context->StIIP;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = context->IntSp;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrBStore.Offset = context->RsBSP;
	frame.AddrBStore.Mode = AddrModeFlat;
	frame.AddrStack.Offset = context->IntSp;
	frame.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif // _M_IX86

	size_t recursionCount = 0;
	for (size_t frameNum = 0; ; ++frameNum) {
		// walk each frame
		if (!StackWalk64(machineType, GetCurrentProcess(), GetCurrentThread(), &frame, context,
						 nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr)) {

				LOG(ERROR) << "SymHandler::captureStackTrace: StackWalk64 failed.";
				break;
		}

		// prevent hangup on endless recursion
		if (frame.AddrPC.Offset == frame.AddrReturn.Offset) {
			if (recursionCount > MAX_RECURSION_DEEP) {
				// TODO log endless stack.
				LOG(ERROR) << "SymHandler::captureStackTrace: Infinite recursion.";
				break;
			}
			recursionCount++;
		} else
			recursionCount = 0;

		if (frame.AddrPC.Offset != 0 && frameNum >= skip)
			framePtrs.push_back(frame.AddrPC.Offset);

		if (frame.AddrReturn.Offset == 0)
			break;
	}
}

SymbolInfo SymHandler::getSymbolInfo(uint64_t addr) {
	if (!isInitialized)
		throw std::logic_error("SymHandler is not initialized");

	DWORD64  displacement = 0;
	char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
	SYMBOL_INFO* symbol = (SYMBOL_INFO*)buffer;

	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	symbol->MaxNameLen = MAX_SYM_NAME;

	SymbolInfo ret(addr);

	if (SymFromAddr(GetCurrentProcess(), addr, &displacement, symbol)) {
		ret.name = symbol->Name;

		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		DWORD lineDisplacement = 0;
		if (SymGetLineFromAddr64(GetCurrentProcess(), addr, &lineDisplacement, &line)) {
			ret.fileName = line.FileName;
			ret.lineNumber = line.LineNumber;
		} else
			LOG(WARNING) << "SymGetLineFromAddr64: failed. [" << GetLastError() << "]" ;
	} else
		LOG(WARNING) << "SymFromAddr: failed. [" << GetLastError() << "]" ;

	return ret;
}