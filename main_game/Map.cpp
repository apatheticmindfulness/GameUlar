#include "Map.h"
#include "Config.h"
#include "Utils.h"

Map::Map(const int mapWidth, const int mapHeight)
	:
	width(mapWidth),
	height(mapHeight)
{}

Map::~Map()
{}

int Map::GetWidth() const
{
	return width;
}

int Map::GetHeight() const
{
	return height;
}

void Map::Draw()
{
	for (int y = 1; y < height; ++y)
	{
		float map = (float)CANVAS_HEIGHT / (float)height;
		float height = map * y;

		DrawLine(1.0f, height, (float)CANVAS_WIDTH - 1.0f, height, COLOR_BLACK);
	}

	for (int x = 1; x < width; ++x)
	{
		float map = (float)CANVAS_WIDTH / (float)width;
		float width = map * x;

		DrawLine(width, 1.0f, width, (float)CANVAS_HEIGHT - 1.0f, COLOR_BLACK);
	}
}
