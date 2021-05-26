#pragma once

#include <string>

#include "export.h"

extern "C" {
API const char* hello();
API int sum(int x, int y);
API double add_double(int x, double y);
}
