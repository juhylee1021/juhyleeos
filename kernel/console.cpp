#include <cstring>
#include "console.hpp"
#include "font.hpp"

Console::Console(PixelWriter& writer, const RGB_t bgColor, const RGB_t fgColor)
	: mWriter(writer)
	, mBGColor(bgColor)
	, mFGColor(fgColor)
	, mCursorPosRow(0)
	, mCursorPosCol(0)
	, mBuffer{}
{
}

void Console::PutString(const char* str)
{
	while (*str)
	{
		if (mCursorPosCol == MAX_COL)
		{
			feedLine();
			continue;
		}
		if (*str == '\n')
		{
			feedLine();
		}
		else
		{
			WriteAscii(mWriter, 8 * mCursorPosCol, 16 * mCursorPosRow, *str, mFGColor);
			mBuffer[mCursorPosRow][mCursorPosCol] = *str;
			++mCursorPosCol;
		}
		++str;
	}
}

void Console::clear()
{
	for (int y = 0; y < 16 * MAX_ROW; ++y)
	{
		for (int x = 0; x < 8 * MAX_COL; ++x)
		{
			mWriter.Write(x, y, mBGColor);
		}
	}
	return;
}

void Console::feedLine()
{
	mCursorPosCol = 0;
	if (mCursorPosRow < MAX_ROW - 1)
	{
		++mCursorPosRow;
		return;
	}
	this->clear();
	for (int row = 0; row < MAX_ROW - 1; ++row)
	{
		memcpy(mBuffer[row], mBuffer[row + 1], MAX_COL + 1);
		WriteString(mWriter, 0, 16 * row, mBuffer[row], mFGColor);
	}
	mBuffer[MAX_ROW - 1][MAX_COL] = '\0';
	return;
}
