#pragma once

#include "graphics.hpp"

class Console
{
public:
	Console() = delete;
	Console(const Console& other) = delete;
	Console& operator=(const Console& other) = delete;
	Console(PixelWriter& writer, const RGB_t bgColor, const RGB_t fgColor);
	virtual ~Console() = default;

	void PutString(const char* str);
protected:
private:
	void clear();
	void feedLine();

protected:
private:
	enum
	{
		MAX_ROW = 25,
		MAX_COL = 80
	};
	PixelWriter& mWriter;
	RGB_t mBGColor;
	RGB_t mFGColor;
	int mCursorPosRow;
	int mCursorPosCol;
	char mBuffer[MAX_ROW][MAX_COL + 1];
};
