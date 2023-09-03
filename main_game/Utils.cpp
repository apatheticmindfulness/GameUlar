#include "Utils.h"
#include "iki_basic_graphics.h"

#include <math.h>

void DrawRectCR(const RECT src, const RECT dst, iki_color color)
{
	int dstRight = dst.left + dst.right;
	int dstBottom = dst.top + dst.bottom;

	int srcLeft = src.left;
	int srcTop = src.top;
	int srcRight = src.left + src.right;
	int srcBottom = src.top + src.bottom;

	if (srcLeft < dst.left)
	{
		srcLeft = dst.left;
	}
	if (srcRight > dstRight)
	{
		srcRight = dstRight;
	}

	if (srcBottom > dstBottom)
	{
		srcBottom = dstBottom;
	}
	if (srcTop < dst.top)
	{
		srcTop = dst.top;
	}


	for (int y = srcTop; y < srcBottom; ++y)
	{
		for (int x = srcLeft; x < srcRight; ++x)
		{
			IkiSetPixel(x, y, color);
		}
	}
}

void Swap(float* x, float* y)
{
	float temp = *x;
	*x = *y;
	*y = temp;
}

void DrawLine(float x0, float y0, float x1, float y1, iki_color color)
{
	float xStart = x0;
	float xEnd = x1;

	float yStart = y0;
	float yEnd = y1;

	float m = 0.0f;

	if (xStart != xEnd)
	{
		m = (yEnd - yStart) / (xEnd - xStart);
	}

	float b = y0 - m * x0;

	if (xStart > xEnd)
	{
		Swap(&xStart, &xEnd);
	}

	if (abs((int)m) < 1.0f && xStart != xEnd)
	{
		for (int x = (int)xStart; x < (int)xEnd; ++x)
		{
			const float y = (m * x) + b;

			IkiSetPixel(x, (int)y, color);
		}
	}
	else
	{
		float w = (x1 - x0) / (y1 - y0);
		float p = x0 - w * y0;

		if (yStart > yEnd)
		{
			Swap(&yStart, &yEnd);
		}

		for (int y = (int)yStart; y < (int)yEnd; ++y)
		{
			float x = (w * (float)y) + p;
			IkiSetPixel((int)x, y, color);
		}
	}

}

void DrawRect(RECT rect, iki_color color)
{
	//int bottom = rect.top + rect.bottom;
	//int right = rect.left + rect.right;
	//
	//for (int y = rect.top; y < bottom; ++y)
	//{
	//	for (int x = rect.left; x < right; ++x)
	//	{
	//		IkiSetPixel(x, y, color);
	//	}
	//}

	// This might need to be fix
	DrawRectCR(rect, { 0, 0, 700, 700 }, color);
}
