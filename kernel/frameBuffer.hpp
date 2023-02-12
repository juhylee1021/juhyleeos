#pragma once

#include <stdint.h>

typedef enum
{
	E_PIXEL_FORMAT_RGB_REVERSE_8BIT,
	E_PIXEL_FORMAT_BGR_REVERSE_8BIT,
} EPixelFormat;

struct FrameBuffer
{
	uint8_t* base;
	uint32_t size;
	uint32_t pixelsPerScanLine;
	uint32_t horizontalResolution;
	uint32_t verticalResolution;
	EPixelFormat pixelFormat;
};
