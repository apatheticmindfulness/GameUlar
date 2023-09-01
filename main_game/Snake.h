#pragma once

#include "Utils.h"

typedef struct Snake_T
{
	int maxBody;

	bool isHead;
	bool isBody;
	iki_color color;

	Vector2Int pos;
	Vector2Int direction;
	RECT rect;
} Snake;