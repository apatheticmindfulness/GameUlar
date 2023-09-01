#include "Utils.h"
#include "iki_basic_graphics.h"

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
