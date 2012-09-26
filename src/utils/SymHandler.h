#pragma once

#include <vector>
#include <cstdint>

struct SymbolInfo 
{
	SymbolInfo(uint64_t addr) : addr(addr) { }

	std::string name;
	uint64_t addr;
	std::string fileName;
	unsigned long lineNumber;
};

typedef struct _CONTEXT CONTEXT;

/**
 * Singleton class that wraps some useful DbgHelp calls.
 * This class is not thread-safe!
 */
class SymHandler
{
public:
	/// Return instance of this singleton
	static SymHandler& instance();

	/**
	 * Get info about symbol.
	 * @param addr address of symbol
	 * @return info about symbol
	 */
	SymbolInfo getSymbolInfo(uint64_t addr);
	/**
	 * Capture stack trace in given context using WinAPIs @link{StackWalk64}.
	 * @retval framePtrs addresses of captured frames.
	 * @param skip number of first frames that won't be returned.
	 * @param context where to capture trace. if nullptr, function will get current context.
	 */
	void captureStackTrace(std::vector<uint64_t>& framePtrs, size_t skip = 0, CONTEXT* context = nullptr);
private:
	static const int MAX_RECURSION_DEEP = 1000;

	SymHandler();
	~SymHandler();

	bool isInitialized;
};

