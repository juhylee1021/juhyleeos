#pragma once

#include <cstdint>
#include "graphics.hpp"

void WriteAscii(PixelWriter& pw, int x, int y, char ch, const RGB_t& colo);
void WriteString(PixelWriter& pw, int x, int y, const char* str, const RGB_t& colo);
