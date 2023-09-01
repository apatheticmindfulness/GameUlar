#pragma once
#include "iki_window_win.h"
#include "iki_color.h"

typedef struct
{
	int x;
	int y;
} Vector2Int;

void DrawRectCR(const RECT src, const RECT dst, iki_color color);