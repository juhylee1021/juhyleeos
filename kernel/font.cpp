#include "font.hpp"

extern const uint8_t _binary_hankaku_bin_start;
extern const uint8_t _binary_hankaku_bin_end;
extern const uint8_t _binary_hankaku_bin_size;

const uint8_t* GetFont(char c)
{
  auto index = 16 * static_cast<unsigned int>(c);
  if (index >= reinterpret_cast<uintptr_t>(&_binary_hankaku_bin_size))
	{
    return nullptr;
  }
  return &_binary_hankaku_bin_start + index;
}

void WriteAscii(PixelWriter& pw, int x, int y, char ch, const RGB_t& colo)
{
  const uint8_t* font = GetFont(ch);
  if (font == nullptr)
	{
    return;
  }
  for (int dy = 0; dy < 16; ++dy)
	{
    for (int dx = 0; dx < 8; ++dx)
		{
      if ((font[dy] << dx) & 0x80u)
			{
        pw.Write(x + dx, y + dy, colo);
      }
    }
  }
	return;
}
