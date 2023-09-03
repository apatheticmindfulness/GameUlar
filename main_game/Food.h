#pragma once

#include "Utils.h"
#include "Map.h"
#include "Snake.h"

struct Food
{
public:
	Food(const Vector2Int startPosition, const iki_color startColor);
	~Food();
	bool IsEaten() const;
	void Eaten();

	Vector2Int GetPosition() const;

	void SetPosition(const Vector2Int newPos);

	void Update(float dt, const Map map);
	void Draw();

private:
	bool isEaten;
	Vector2Int pos;
	iki_color color;
	RECT rect;
};