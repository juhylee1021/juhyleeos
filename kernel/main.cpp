#include <cstddef>
#include <cstdint>
#include <cstdio>
#include "frameBuffer.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

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

  for (int i = 0; i < 42; ++i) {
    printk("printk: %d\n", i);
  }

	while(1)
	{
		__asm__("hlt");
	}
	return;
}
