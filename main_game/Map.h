#pragma once

struct Map
{
public:
	Map(const int mapWidth, const int mapHeight);
	~Map();

	int GetWidth() const;
	int GetHeight() const;
	void Draw();

private:
	int width;
	int height;
};