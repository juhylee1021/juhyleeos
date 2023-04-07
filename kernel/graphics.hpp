#pragma once

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

template<typename T>
struct Vector2D
{
	template<typename U>
	Vector2D<T>& operator+=(const Vector2D<U>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	T x;
	T y;
};

void FillRactangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const RGB_t& color);
void DrawRactangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const RGB_t& color);
