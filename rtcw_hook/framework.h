#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <Psapi.h>
#include <cstring>
#include <memory>

#pragma comment(lib, "detours.lib")

#include "detours.h"