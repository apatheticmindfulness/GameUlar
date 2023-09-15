#pragma once

#include "Utils.h"
#include "Map.h"

struct Snake
{
	bool isHead;
	bool isBody;
	iki_color color;
	Vector2Int pos;
	Vector2Int direction;
	RECT rect;
};

enum SnakeMovement
{
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_NONE
};

struct SnakeContainer
{
public:
	SnakeContainer(const int maxBody);
	~SnakeContainer();

	void InitializeHead(const Vector2Int startPosition, 
						const Vector2Int startDirection,
						const iki_color color);

	void FreeSnakeContainer();

	bool IsHeadInitialized() const;
	
	void SetPosition(Vector2Int position);
	Vector2Int GetPosition() const;

	int GetLength() const;
	int GetMaxLength() const;
	Snake * GetSnakes() const;

	SnakeMovement GetDirection() const;

	void Grow();


	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	bool CheckObstacle(const Map map) const;

	void Update(float dt, const Map map);
	void Draw(const Map map);

private:
	int maxBodySize;
	int currentBodyIndex;
	bool isHeadInitialzed;

	float moveCounter;
	float moveDuration;

	SnakeMovement snakeMovement;
	Snake * snakes;
};

