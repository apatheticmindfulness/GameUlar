#include "Game.h"

Game::Game()
	:
	state(GAME_RUNNING),
	score(0),
	seed(rd()),
	map(20, 20),
	snake(4),
	food({5, 5}, COLOR_GREEN)
{}

Game::~Game()
{}

void Game::Initialize()
{
	std::uniform_int_distribution<> snakePosX(1, map.GetWidth() - 2);
	std::uniform_int_distribution<> snakePosY(1, map.GetHeight() - 2);

	Vector2Int snakeStartPosition;
	snakeStartPosition.x = snakePosX(seed);
	snakeStartPosition.y = snakePosY(seed);

	Vector2Int snakeStartDirection = { 0, 0 };
	iki_color snakeHeadColor = { 81, 0, 0, 255 };
	
	if (!snake.IsHeadInitialized())
	{
		snake.InitializeHead(snakeStartPosition, snakeStartDirection, snakeHeadColor);
	}
	else
	{
		score = 0;
		snake.FreeSnakeContainer();
		snake.InitializeHead(snakeStartPosition, snakeStartDirection, snakeHeadColor);
	}

	bool generate = true;

	Vector2Int foodPosition;
	while (generate)
	{
		std::uniform_int_distribution<> foodPosX(1, map.GetWidth() - 2);
		std::uniform_int_distribution<> foodPosY(1, map.GetHeight() - 2);

		foodPosition.x = foodPosX(seed);
		foodPosition.y = foodPosY(seed);

		if (foodPosition.x != snakeStartPosition.x &&
			foodPosition.y != snakeStartPosition.y)
		{
			generate = false;
		}
	}

	food.SetPosition(foodPosition);
}

void Game::Update(float dt)
{
	if (IkiKeyboardIsPressed(VK_ESCAPE))
	{
		IkiCloseWindow();
	}

	if (state == GAME_OVER)
	{
		if (IkiKeyboardIsPressed('R'))
		{
			state = GAME_START;
		}
	}

	if (state == GAME_START)
	{
		Initialize();
		state = GAME_RUNNING;
	}

	if (state == GAME_RUNNING)
	{
		if (IkiKeyboardIsPressed('D'))
		{
			if (snake.GetLength() <= 1)
			{
				snake.MoveRight();
			}
			else
			{
				if (snake.GetDirection() != MOVE_LEFT)
				{
					snake.MoveRight();
				}
			}
		}
		else if (IkiKeyboardIsPressed('A'))
		{
			if (snake.GetLength() <= 1)
			{
				snake.MoveLeft();
			}
			else
			{
				if (snake.GetDirection() != MOVE_RIGHT)
				{
					snake.MoveLeft();
				}
			}
		}
		else if (IkiKeyboardIsPressed('W'))
		{
			if (snake.GetLength() <= 1)
			{
				snake.MoveUp();
			}
			else
			{
				if (snake.GetDirection() != MOVE_DOWN)
				{
					snake.MoveUp();
				}
			}

		}
		else if (IkiKeyboardIsPressed('S'))
		{
			if (snake.GetLength() <= 1)
			{
				snake.MoveDown();
			}
			else
			{
				if (snake.GetDirection() != MOVE_UP)
				{
					snake.MoveDown();
				}
			}
		}
	}

	if (score == snake.GetMaxLength() - 1)
	{
		state = GAME_WIN;
	}

	if (snake.GetPosition().x == food.GetPosition().x &&
		snake.GetPosition().y == food.GetPosition().y)
	{
		score += 1;

		food.Eaten();

		// Grow the snake
		snake.Grow();

		// Update the food position
		bool generate = true;
		bool foodIsInsideTheSnakeBody = false;
		Vector2Int newPosition = { 0 };

		while (generate)
		{
			std::uniform_int_distribution<> newPosX(1, map.GetWidth() - 2);
			std::uniform_int_distribution<> newPosY(1, map.GetHeight() - 2);

			newPosition.x = newPosX(seed);
			newPosition.y = newPosY(seed);

			for (int i = 0; i < snake.GetLength(); ++i)
			{
				if (newPosition.x == snake.GetSnakes()[i].pos.x &&
					newPosition.y == snake.GetSnakes()[i].pos.y)
				{
					foodIsInsideTheSnakeBody = true;
				}
			}

			if (!foodIsInsideTheSnakeBody)
			{
				generate = false;
			}
			else
			{
				foodIsInsideTheSnakeBody = false;
			}
		}

		food.SetPosition(newPosition);
	}

	if (!snake.CheckObstacle(map))
	{
		if (state != GAME_WIN)
		{
			snake.Update(dt, map);
		}
	}
	else
	{
		state = GAME_OVER;
	}

	food.Update(dt, map);
}


void Game::Draw()
{
	char buffer[100];

	if (state == GAME_OVER)
	{
		sprintf_s(buffer, "Game Over | Score: %d | Click R to restart, ESC for quit", score);
	}
	else if (state == GAME_WIN)
	{
		sprintf_s((buffer), "Congratulations you've reached the maximum length of the snake %d", score);
		int message = MessageBox((HWND)IkiGetWindowHandle(), buffer, "You win", MB_OK);
		if (message == IDOK)
		{
			state = GAME_START;
		}
	}
	else
	{
		sprintf_s(buffer, "Score: %d", score);
	}

	SetWindowText((HWND)IkiGetWindowHandle(), buffer);

	IkiClearBackground({ 202, 176, 142, 1 });

	map.Draw();
	
	if (!food.IsEaten())
	{
		food.Draw();
	}

	snake.Draw(map);
}

void Game::End()
{
	snake.FreeSnakeContainer();
}
