#include <gtest/gtest.h>
#include <sstream>

#include "..\Utils\Exception.h"

void bar() {
	throw Exception("test");
}

void foo() {
	bar();
}

TEST(ExceptionsTest, NoThrow) {
	std::ostringstream s;
	try {
		foo();
	} catch (Exception& e) {
		e.printStackTrace(s);
	}
	EXPECT_FALSE(s.str().empty());
}

TEST(ExceptionsTest, Win32) {
	std::ostringstream s;
	try {
		throw Win32Exception("Sample Win32 Error", ERROR_FILE_NOT_FOUND, true);
	} catch (Exception& e) {
		e.printStackTrace(s);
	}
	EXPECT_FALSE(s.str().empty());
}