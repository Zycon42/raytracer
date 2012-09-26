#include "File.h"

#include "Exception.h"
#include "common.h"

// without NOGDI there's name conflict with glog (windows define ERROR macro)
#define NOGDI
#include <Windows.h>

class File::Impl
{
public:
	File::Impl(File* f) : f(f), handle(INVALID_HANDLE_VALUE), errCode(0) { }

	bool isOpened() const {
		return handle != INVALID_HANDLE_VALUE;
	}

	void open(OpenMode mode);

	std::string name;
	HANDLE handle;
	DWORD errCode;
private:
	File* f;
};

File::File(const std::string& fileName, OpenMode mode) : impl(new File::Impl(this)) {
	impl->name = fileName;
	impl->open(mode);
}

File::~File() {
	close();
}

void File::close() {
	if (impl->isOpened()) {
		CloseHandle(impl->handle);
		impl->handle = INVALID_HANDLE_VALUE;
	}
}

void File::Impl::open(OpenMode mode) {
	if (isOpened() || name.empty())
		throw Exception("File is already opened or fileName not set.");

	DWORD access = 0, shareMode = 0, creationDisposition = 0;
	switch (mode)
	{
	case File::OpenMode::ReadOnly:
		access = GENERIC_READ;
		shareMode = FILE_SHARE_READ;
		creationDisposition = OPEN_EXISTING;
		break;
	}

	handle = CreateFileA(name.c_str(), access, shareMode, 
		nullptr, creationDisposition, 0, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		throw Win32Exception("CreateFile failed", true);
}

std::string File::name() const {
	return impl->name;
}

size_t File::size() const {
	if (!impl->isOpened())
		throw Exception("File is not opened.");

	LARGE_INTEGER s;
	if (!GetFileSizeEx(impl->handle, &s))
		throw Win32Exception("GetFileSizeEx failed");

	return static_cast<size_t>(s.QuadPart);
}

size_t File::readData(void* buff, size_t size) {
	DWORD nbytes;
	if (!ReadFile(impl->handle, buff, size, &nbytes, nullptr))
		throw Win32Exception("ReadFile failed");

	return nbytes;
}

std::vector<char> File::readAll() {
	std::vector<char> res(size());
	readData(static_cast<void*>(res.data()), res.size());
	return res;
}
