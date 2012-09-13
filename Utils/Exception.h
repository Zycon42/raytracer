#pragma once

#include "SymHandler.h"

#ifndef PRECOMPILED_HEADERS_INCLUDED
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>
#endif // !PRECOMPILED_HEADERS_INCLUDED

class Exception : public std::runtime_error
{
public:
	Exception(bool generateStackTrace = true);
	Exception(const std::string& msg, bool generateStackTrace = true);

	virtual ~Exception() throw();

	/// Alternate name for what().
	const char* message() const { return what(); }

	/// Get exception stack trace. Symbols are lazy loaded on first call of this function.
	std::vector<SymbolInfo> stackTrace();
	/// Print exception stack trace to specified stream.
	void printStackTrace(std::ostream& stream = std::cerr);
private:
	void fillInStackTrace();

	std::vector<uint64_t> frameAddrs;
	std::vector<SymbolInfo> frameSymbols;
};

class Win32Exception : public Exception
{
public:
	Win32Exception(bool generateStackTrace = true);
	Win32Exception(const std::string& msg, bool generateStackTrace = true);
	Win32Exception(const std::string& msg, uint32_t errorCode, bool generateStackTrace = true);
	Win32Exception(uint32_t errorCode, bool generateStackTrace = true);
private:
	static std::string createMessage(const std::string& msg, uint32_t errorCode);
};

class Win32Error
{
public:
	Win32Error(uint32_t code) : ecode(code) {}
	uint32_t code() const { return ecode; }

	std::string message() const;
private:
	uint32_t ecode;
};
