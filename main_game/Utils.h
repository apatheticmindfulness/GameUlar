#pragma once
#include "iki_window_win.h"
#include "iki_color.h"

struct Vector2Int
{
	int x;
	int y;
};

void DrawRectCR(const RECT src, const RECT dst, iki_color color);

void Swap(float* x, float* y);

void DrawLine(float x0, float y0, float x1, float y1, iki_color color);

void DrawRect(RECT rect, iki_color color);