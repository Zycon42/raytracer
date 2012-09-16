#include <gtest/gtest.h>

#include <windows.h>

#include <fstream>

#include "../Utils/File.h"

class FileTest : public ::testing::Test
{
protected:
	static void SetUpTestCase() {
		char pathBuff[MAX_PATH + 1];
		if (!GetTempPathA(MAX_PATH, pathBuff))
			throw std::runtime_error("GetTempPath failed");

		char tmpBuff[MAX_PATH + 1];
		if (!GetTempFileNameA(pathBuff, "test", 0, tmpBuff))
			throw std::runtime_error("GetTempFileName failed");
		tmpFile.assign(tmpBuff);

		std::ofstream stream(tmpFile.c_str());
		stream << content;
	}

	static void TearDownTestCase() {
		DeleteFileA(tmpFile.c_str());
	}

	static std::string tmpFile;
	static const char* content;
};

std::string FileTest::tmpFile = "";
const char* FileTest::content = "test content";

TEST_F(FileTest, Read) {
	File file(tmpFile, File::OpenMode::ReadOnly);
	auto buff = file.readAll();

	std::string readContent(buff.data(), buff.size());
	EXPECT_STREQ(content, readContent.c_str());
}