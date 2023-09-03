#include "Game.h"

Game::Game()
	:
	seed(rd()),
	map(20, 20),
	snake(100),
	food({10, 7}, COLOR_GREEN)
{}

Game::~Game()
{}

void Game::Initialize()
{
	std::random_device rd;
	std::mt19937 seed(rd());

	Vector2Int snakeStartPosition = { 2, 2 };
	Vector2Int snakeStartDirection = { 1, 0 };
	iki_color snakeHeadColor = { 81, 0, 0, 255 };
	
	snake.InitializeHead(snakeStartPosition, snakeStartDirection, snakeHeadColor);
}

void Game::Update(float dt)
{
	if (IkiKeyboardIsPressed(VK_ESCAPE))
	{
		IkiCloseWindow();
	}


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


	if (snake.GetPosition().x == food.GetPosition().x &&
		snake.GetPosition().y == food.GetPosition().y)
	{
		food.Eaten();

		// Grow the snake
		snake.Grow();

		// Update food position
		bool generate = true;
		bool foodIsInsideTheSnakeBody = false;
		Vector2Int newPosition = { 0 };

		while (generate)
		{
			std::uniform_int_distribution<> newPosX(0, map.GetWidth() - 1);
			std::uniform_int_distribution<> newPosY(0, map.GetHeight() - 1);

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

	snake.Update(dt, map);

	food.Update(dt, map);
}


void Game::Draw()
{
	IkiClearBackground(COLOR_GRAY);

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
