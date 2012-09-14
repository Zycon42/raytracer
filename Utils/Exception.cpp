#include "stdafx.h"
#include "Exception.h"

static std::string fileBaseName(const std::string& path) {
	size_t del = path.rfind('\\');
	return path.substr(del == std::string::npos ? 0 : del + 1);
}

Exception::Exception(bool generateStackTrace /* = true */) : std::runtime_error("Exception") {
	if (generateStackTrace)
		fillInStackTrace();
}

Exception::Exception(const std::string& msg, bool generateStackTrace /* = true */) : std::runtime_error(msg) {
	if (generateStackTrace)
		fillInStackTrace();
}

Exception::~Exception() {
}

void Exception::fillInStackTrace() {
	try {
		SymHandler::instance().captureStackTrace(frameAddrs, 2);
	} catch (std::exception& e) {
		LOG(ERROR) << "Exception::fillInStackTrace: caught std::exception with message: " << e.what();
	}
}

std::vector<SymbolInfo> Exception::stackTrace() {
	if (frameAddrs.empty() || !frameSymbols.empty())
		return frameSymbols;

	for (uint64_t addr : frameAddrs) {
		frameSymbols.push_back(SymHandler::instance().getSymbolInfo(addr));
	}
	return frameSymbols;
}

void Exception::printStackTrace(std::ostream& stream /* = std::cerr */) {
	// make sure we have symbols generated.
	stackTrace();

	stream << typeid(*this).name() << ": " << message() << std::endl;
	for (SymbolInfo symbol : frameSymbols) {
		stream << "\tat ";
		if (symbol.name.empty())
			stream << "?? ";
		else {
			stream << symbol.name << " ";
		}

		if (symbol.fileName.empty())
			stream << "[0x" << std::hex << symbol.addr << "]" << std::endl;
		else
			stream << "(" << fileBaseName(symbol.fileName) << ":" << std::dec << symbol.lineNumber << ")" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, Exception& e) {
	e.printStackTrace(out);
	return out;
}

Win32Exception::Win32Exception(uint32_t errorCode, bool generateStackTrace /* = true */)
	: Exception(createMessage(std::string(), errorCode), generateStackTrace) { }

Win32Exception::Win32Exception(bool generateStackTrace /* = true */)
	: Exception(createMessage(std::string(), GetLastError()), generateStackTrace) { }

Win32Exception::Win32Exception(const std::string& msg, bool generateStackTrace /* = true */)
	: Exception(createMessage(msg, GetLastError()), generateStackTrace) { }

Win32Exception::Win32Exception(const std::string& msg, uint32_t errorCode, bool generateStackTrace /* = true */)
	: Exception(createMessage(msg, errorCode), generateStackTrace) { }

std::string Win32Exception::createMessage(const std::string& msg, uint32_t errorCode) {
	std::ostringstream s;
	s << msg << " [" << errorCode << "] " << Win32Error(errorCode).message();
	return s.str();
}

struct LocalFreeHelper
{
	void operator()(void* ptr) {
		LocalFree(ptr);
	}
};

std::string Win32Error::message() const {
	// use unique_ptr to gain exception safety
	std::unique_ptr<void, LocalFreeHelper> buff;
	LPSTR buffPtr;
	DWORD bufferLength = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		ecode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&buffPtr),
		0,
		NULL);
	buff.reset(buffPtr);
	return std::string(buffPtr, bufferLength);
}