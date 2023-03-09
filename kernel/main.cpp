#include <cstddef>
#include <cstdint>
#include <cstdio>
#include "frameBuffer.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

RGB_t gBGColor = {54, 55, 69};
RGB_t gFGColor = {213, 215, 235};

void* operator new(size_t, void* buf)
{
	return buf;
}

void operator delete(void*) noexcept
{
}

char gPixelWriterBuffer[sizeof(RGBReversePixelWriter)];
PixelWriter* gPixelWriterPtr;
char gConsoleBuffer[sizeof(Console)];
Console* gConsolePtr;

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
	char buf[128];
	for (int row = 0; row < 32; ++row)
	{
		sprintf(buf, "Line: %d\n", row);
		gConsolePtr->PutString(buf);
	}
	while(1)
	{
		__asm__("hlt");
	}
	return;
}
