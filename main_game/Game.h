#pragma once
#include <random>

#include "iki_window.h"
#include "iki_basic_graphics.h"
#include "iki_time.h"

#include "Map.h"
#include "Snake.h"
#include "Food.h"

enum GameState
{
	GAME_START,
	GAME_RUNNING,
	GAME_PAUSE,
	GAME_OVER,
	GAME_WIN
};

struct Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Update(float dt);
	void Draw();
	void End();

private:
	int score;
	GameState state;

	std::random_device rd;
	std::mt19937 seed;

	Map map;
	SnakeContainer snake;
	Food food;
};