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
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float posX = (float)x * ((float)CANVAS_WIDTH / (float)width);
			float posY = (float)y * ((float)CANVAS_HEIGHT / (float)height);

			RECT rect = { 0 };
			rect.left = (int)posX;
			rect.top = (int)posY;
			rect.right = (int)((float)CANVAS_WIDTH / (float)width);
			rect.bottom = (int)((float)CANVAS_HEIGHT / (float)height);

			if (y == 0 || y == (height - 1) || x == 0 || x == (width - 1))
			{
				iki_color color = IkiColorFromHex(0x474646);
				DrawRect(rect, {0, 0, CANVAS_WIDTH, CANVAS_HEIGHT}, color);
			}

			if (x > 0 && y > 0)
			{
				float mapHeight = (float)CANVAS_HEIGHT / (float)height;
				float height = mapHeight * y;

				DrawLine(1.0f, height, (float)CANVAS_WIDTH - 1.0f, height, COLOR_BLACK);

				float mapWidth = (float)CANVAS_WIDTH / (float)width;
				float width = mapWidth * x;

				DrawLine(width, 1.0f, width, (float)CANVAS_HEIGHT - 1.0f, COLOR_BLACK);
			}

		}
	}
}
