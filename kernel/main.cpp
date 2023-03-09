#include <cstddef>
#include <cstdint>
#include "frameBuffer.hpp"
#include "graphics.hpp"
#include "font.hpp"

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

	for (uint32_t y = 0; y < fb->verticalResolution; ++y)
	{
		for (uint32_t x = 0; x < fb->horizontalResolution; ++x)
		{
			gPixelWriterPtr->Write(x, y, gBGColor);
		}
	}
	for (uint32_t y = 0; y < 200; ++y)
	{
		for (uint32_t x = 0; x < 100; ++x)
		{
			gPixelWriterPtr->Write(x, y, gFGColor);
		}
	}

	int i = 0;
	for (char c = '!'; c <= '~'; ++c, ++i)
	{
		WriteAscii(*gPixelWriterPtr, 32 + 8 * i, 300, c, gFGColor);
	}

	while(1)
	{
		__asm__("hlt");
	}
	return;
}
