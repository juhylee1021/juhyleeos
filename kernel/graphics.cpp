#include "graphics.hpp"

void FillRactangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const RGB_t& color)
{
	for (int dy = 0; dy < size.y; ++dy)
	{
		for (int dx = 0; dx < size.x; ++dx)
		{
			writer.Write(pos.x + dx, pos.y + dy, color);
		}
	}
	return;
}
void DrawRactangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const RGB_t& color)
{
	for (int dx = 0; dx < size.x; ++dx)
	{
		writer.Write(pos.x + dx, pos.y, color);
		writer.Write(pos.x + dx, pos.y + size.y, color);
	}
	for (int dy = 0; dy < size.y; ++dy)
	{
		writer.Write(pos.x, pos.y + dy, color);
		writer.Write(pos.x + size.x, pos.y + dy, color);
	}
	return;
}
