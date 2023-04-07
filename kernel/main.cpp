#include <cstddef>
#include <cstdint>
#include <cstdio>
#include "frameBuffer.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

const int gMouseCursorWidth = 15;
const int gMouseCursorHeight = 24;
const char mouseCursorShape[gMouseCursorHeight][gMouseCursorWidth + 1] =
{
  "@              ",
  "@@             ",
  "@.@            ",
  "@..@           ",
  "@...@          ",
  "@....@         ",
  "@.....@        ",
  "@......@       ",
  "@.......@      ",
  "@........@     ",
  "@.........@    ",
  "@..........@   ",
  "@...........@  ",
  "@............@ ",
  "@......@@@@@@@@",
  "@......@       ",
  "@....@@.@      ",
  "@...@ @.@      ",
  "@..@   @.@     ",
  "@.@    @.@     ",
  "@@      @.@    ",
  "@       @.@    ",
  "         @.@   ",
  "         @@@   ",
};

RGB_t gBGColor = {54, 55, 69};
RGB_t gFGColor = {213, 215, 235};

char gPixelWriterBuffer[sizeof(RGBReversePixelWriter)];
PixelWriter* gPixelWriterPtr;
char gConsoleBuffer[sizeof(Console)];
Console* gConsolePtr;

void* operator new(size_t, void* buf)
{
	return buf;
}

void operator delete(void*) noexcept
{
}

int printk(const char* format, ...)
{
  va_list ap;
  int result;
  char buf[1024];

  va_start(ap, format);
  result = vsprintf(buf, format, ap);
  va_end(ap);

  gConsolePtr->PutString(buf);
  return result;
}

extern "C"
void KernelMain(FrameBuffer* fb)
{
	switch (fb->pixelFormat)
	{
		case E_PIXEL_FORMAT_RGB_REVERSE_8BIT:
			gPixelWriterPtr = new(gPixelWriterBuffer)RGBReversePixelWriter(*fb);
			break;
		case E_PIXEL_FORMAT_BGR_REVERSE_8BIT:
			gPixelWriterPtr = new(gPixelWriterBuffer)BGRReversePixelWriter(*fb);
			break;
		default:
			while(1)__asm("hlt");
	}
	gConsolePtr = new(gConsoleBuffer)Console(*gPixelWriterPtr, gBGColor, gFGColor);
	
	const int frameWidht = fb->horizontalResolution;
	const int frameHeight = fb->verticalResolution;

	FillRactangle(*gPixelWriterPtr, {0, 0}, {frameWidht, frameHeight}, gBGColor);
	FillRactangle(*gPixelWriterPtr, {0, frameHeight - 50}, {frameWidht, 50}, {1, 8, 17});
	FillRactangle(*gPixelWriterPtr, {0, frameHeight - 50}, {50, 50}, {80, 80, 80});
	DrawRactangle(*gPixelWriterPtr, {10, frameHeight - 40}, {30, 30}, {160, 160, 160});
	printk("Hello, It's JuhyleeOS.");

	//render mouse curser
	for (int dy = 0; dy < gMouseCursorHeight; ++dy)
	{
		for (int dx = 0; dx < gMouseCursorWidth; ++dx)
		{
			if (mouseCursorShape[dy][dx] == '@')
			{
				gPixelWriterPtr->Write(200 + dx, 100 + dy, {0, 0, 0});
			}
			else if (mouseCursorShape[dy][dx] == '.')
			{
				gPixelWriterPtr->Write(200 + dx, 100 + dy, {255, 255, 255});
			}
		}
	}

	while(1)
	{
		__asm__("hlt");
	}
	return;
}
