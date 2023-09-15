#include <malloc.h>
#include <assert.h>

#include "Snake.h"
#include "Config.h"


SnakeContainer::SnakeContainer(const int maxBody)
	:
	maxBodySize(maxBody),
	currentBodyIndex(1),
	isHeadInitialzed(false),
	moveCounter(0.0f),
	moveDuration(0.15f),
	snakeMovement(MOVE_NONE),
	snakes(0)
{}

SnakeContainer::~SnakeContainer()
{}

void SnakeContainer::InitializeHead(const Vector2Int startPosition, const Vector2Int startDirection, const iki_color color)
{
	Snake* newSnake = (Snake*)malloc(sizeof(Snake) * maxBodySize);
	if (newSnake)
	{
		for (int i = 1; i < maxBodySize; ++i)
		{
			memset(&newSnake[i], 0, sizeof(Snake));
		}

		newSnake[0].pos = startPosition;
		newSnake[0].direction = startDirection;
		newSnake[0].color = color;

		snakes = newSnake;

		isHeadInitialzed = true;
	}

	snakeMovement = MOVE_NONE;
	currentBodyIndex = 1;
}

void SnakeContainer::SetPosition(Vector2Int position)
{
	assert(IsHeadInitialized());
	snakeMovement = MOVE_NONE;
	snakes[0].pos = position;
}

Vector2Int SnakeContainer::GetPosition() const
{
	assert(IsHeadInitialized());
	return snakes[0].pos;
}

int SnakeContainer::GetLength() const
{
	return currentBodyIndex;
}

int SnakeContainer::GetMaxLength() const
{
	return maxBodySize;
}

Snake* SnakeContainer::GetSnakes() const
{
	assert(IsHeadInitialized());
	return snakes;
}

SnakeMovement SnakeContainer::GetDirection() const
{
	assert(IsHeadInitialized());
	return snakeMovement;
}

void SnakeContainer::FreeSnakeContainer()
{
	if (snakes)
	{
		free(snakes);
		snakes = 0;
	}
}

bool SnakeContainer::IsHeadInitialized() const
{
	return isHeadInitialzed;
}

void SnakeContainer::Grow()
{
	assert(IsHeadInitialized());

	snakes[currentBodyIndex].isBody = true;
	snakes[currentBodyIndex].color = snakes[0].color;

	if (snakes[currentBodyIndex].color.b < 255)
	{
		snakes[currentBodyIndex].color.b += (currentBodyIndex + 20);
	}
	else
	{
		if (snakes[currentBodyIndex].color.g < 255 && snakes[currentBodyIndex].color.r < 255)
		{
			snakes[currentBodyIndex].color.g += 1;
			snakes[currentBodyIndex].color.r += 1;
		}
	}

	snakes[currentBodyIndex].pos = snakes[currentBodyIndex - 1].pos;
	currentBodyIndex += 1;
}

void SnakeContainer::MoveRight()
{
	assert(IsHeadInitialized());
	snakes[0].direction.x = 1;
	snakeMovement = MOVE_RIGHT;
}

void SnakeContainer::MoveLeft()
{
	assert(IsHeadInitialized());
	snakes[0].direction.x = -1;
	snakeMovement = MOVE_LEFT;
}

void SnakeContainer::MoveUp()
{
	assert(IsHeadInitialized());
	snakes[0].direction.y = -1;
	snakeMovement = MOVE_UP;
}

void SnakeContainer::MoveDown()
{
	assert(IsHeadInitialized());
	snakes[0].direction.y = 1;
	snakeMovement = MOVE_DOWN;
}

bool SnakeContainer::CheckObstacle(const Map map) const
{
	assert(IsHeadInitialized());

	int addX = 0;
	int addY = 0;

	if (GetDirection() == MOVE_RIGHT)
	{
		addX = 1;
	}
	else if (GetDirection() == MOVE_LEFT)
	{
		addX = -1;
	}

	else if (GetDirection() == MOVE_UP)
	{
		addY = -1;
	}
	else if (GetDirection() == MOVE_DOWN)
	{
		addY = 1;
	}

	Vector2Int collider = { 0 };
	collider.x = snakes[0].pos.x;
	collider.y = snakes[0].pos.y;

	// Check if the snake's head is hitting its own a part of its body
	for (int i = 2; i < GetLength(); ++i)
	{
		if (collider.x == snakes[i].pos.x &&
			collider.y == snakes[i].pos.y)
		{
			return true;
		}
	}

	if (GetPosition().x == 0 || 
		GetPosition().y == 0 || 
		GetPosition().x == (map.GetWidth() - 1) || 
		GetPosition().y == (map.GetHeight() - 1))
	{
		return true;
	}

	return false;
}

void SnakeContainer::Update(float dt, const Map map)
{
	assert(IsHeadInitialized());

	moveCounter += dt;
	while (moveCounter > moveDuration)
	{
		for (int i = GetLength() - 1; i > 0; --i)
		{
			int previousX = snakes[i - 1].pos.x;
			int previousY = snakes[i - 1].pos.y;

			snakes[i].pos.x = previousX;
			snakes[i].pos.y = previousY;

			snakes[i].rect.left = snakes[i].pos.x * ((CANVAS_WIDTH / map.GetWidth())) + 1;
			snakes[i].rect.top = snakes[i].pos.y * ((CANVAS_WIDTH / map.GetHeight())) + 1;
			snakes[i].rect.right = ((CANVAS_WIDTH / map.GetWidth()) - 1);
			snakes[i].rect.bottom = ((CANVAS_HEIGHT / map.GetHeight()) - 1);
		}

		if (snakeMovement == MOVE_RIGHT || snakeMovement == MOVE_LEFT)
		{
			snakes[0].pos.x += snakes[0].direction.x;
		}
		else
		{
			snakes[0].pos.y += snakes[0].direction.y;
		}

		moveCounter = 0.0f;
	}

	RECT rect = { 0 };
	rect.left = snakes[0].pos.x * ((CANVAS_WIDTH / map.GetWidth())) + 1;
	rect.top = snakes[0].pos.y * ((CANVAS_WIDTH / map.GetHeight())) + 1;
	rect.right = ((CANVAS_WIDTH / map.GetWidth()) - 1);
	rect.bottom = ((CANVAS_HEIGHT / map.GetHeight()) - 1);

	snakes[0].rect = rect;
}

void SnakeContainer::Draw(const Map map)
{
	assert(IsHeadInitialized());

	for (int i = 1; i < GetLength(); ++i)
	{
		DrawRect(snakes[i].rect, {0, 0, CANVAS_WIDTH, CANVAS_HEIGHT}, snakes[i].color);
	}

	DrawRect(snakes[0].rect, {0, 0, CANVAS_WIDTH, CANVAS_HEIGHT}, snakes[0].color);
}
