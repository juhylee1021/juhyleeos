#include <cstddef>
#include <cstdint>

#include "frameBuffer.hpp"

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB_t;

class PixelWriter
{
public:
	PixelWriter() = delete;
	PixelWriter(const FrameBuffer& fb) : mFb(fb) {}
	PixelWriter(const PixelWriter& other) = delete;
	virtual ~PixelWriter() = default;
	PixelWriter& operator=(const PixelWriter& other) = delete;

	virtual void Write(const int x, const int y, const RGB_t& color) = 0;
protected:
	uint8_t* PixelAt(const int x, const int y)
	{
		return mFb.base + 4 * (mFb.pixelsPerScanLine * y + x);
	}
private:

protected:
private:
	const FrameBuffer& mFb;
};

class RGBReversePixelWriter : public PixelWriter
{
public:
	RGBReversePixelWriter(const FrameBuffer& fb) : PixelWriter(fb) {}
	virtual ~RGBReversePixelWriter() = default;

	virtual void Write(const int x, const int y, const RGB_t& color)
	{
		uint8_t* pixel = PixelAt(x, y);
		pixel[0] = color.r;
		pixel[1] = color.g;
		pixel[2] = color.b;
	}
};

class BGRReversePixelWriter : public PixelWriter
{
public:
	BGRReversePixelWriter(const FrameBuffer& fb) : PixelWriter(fb) {}
	virtual ~BGRReversePixelWriter() = default;

	virtual void Write(const int x, const int y, const RGB_t& color)
	{
		uint8_t* pixel = PixelAt(x, y);
		pixel[0] = color.b;
		pixel[1] = color.g;
		pixel[2] = color.r;
	}
};

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
			gPixelWriterPtr->Write(x, y, {255, 255, 255});
		}
	}
	for (uint32_t y = 0; y < 200; ++y)
	{
		for (uint32_t x = 0; x < 100; ++x)
		{
			gPixelWriterPtr->Write(x, y, {0, 0, 255});
		}
	}
	while(1)
	{
		__asm__("hlt");
	}
	return;
}
