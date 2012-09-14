#pragma once

#define PRECOMPILED_HEADERS_INCLUDED

// windows

// without NOGDI there's name conflict with glog (windows define ERROR macro)
#define NOGDI
#include <Windows.h>

// 3rd party
#pragma warning(push)
#pragma warning(disable : 4244)
#include <glog/logging.h>
#pragma warning(pop)

// c++ STL
#include <cstdint>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>
