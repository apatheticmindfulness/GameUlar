#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Config.h"
#include "Game.h"

int main()
{
	const int64_t frequency = IkiGetPerformanceFrequency();
	int64_t startTime = IkiGetPerformanceCounter();
	int64_t endTime = 0;
	int64_t elapsedTime = 0;

	float dt = 0.0f;

	Game game;

	IkiCreateWindow("Map test", WINDOW_WIDTH, WINDOW_HEIGHT);

	IkiUseBasicGraphics(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, 32, false);

	IkiShowWindow();

	UpdateWindow((HWND)IkiGetWindowHandle());

	game.Initialize();

	while (IkiRunProcess())
	{
		game.Update(dt);

		IkiRenderStart();
		game.Draw();
		IkiRenderEnd();

		// Time stuff
		endTime = IkiGetPerformanceCounter();
		elapsedTime = endTime - startTime;
		elapsedTime *= 1000000; // Converts to microseconds to guard againts loss-of-precision
		elapsedTime /= frequency; // (microseconds per frame)

		float millisecondsPerFrame = elapsedTime * (1.0f / 1000.0f);
		float secondsPerFrame = millisecondsPerFrame * (1.0f / 1000.0f);

		dt = secondsPerFrame;

		startTime = endTime;

		Sleep(1);
	}

	game.End();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif


	return 0;
}


#if 0
#include "iki_window.h"
#include "iki_basic_graphics.h"
#include "iki_time.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <random>

#include "Utils.h"
#include "Snake.h"

#include <malloc.h>

#define PI 3.14159
#define TO_DEGREE (180.0f / (float)PI)
#define TO_RADIAN ((float)PI / 180.0f)

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

#define CANVAS_WIDTH WINDOW_WIDTH
#define CANVAS_HEIGHT WINDOW_HEIGHT

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct
{
	bool isEaten;
	iki_color color;

	Vector2Int pos;
	RECT rect;
} Food;

int main()
{
	//constexpr DWORD windowflags = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX;
	//IkiAddWindowFlags(windowflags);

	std::random_device rd;
	std::mt19937 seed(rd());

	const int64_t frequency = IkiGetPerformanceFrequency();
	int64_t startTime = IkiGetPerformanceCounter();
	int64_t endTime = 0;
	int64_t elapsedTime = 0;

	float dt = 0.0f;

	IkiCreateWindow("Map test", WINDOW_WIDTH, WINDOW_HEIGHT);

	IkiUseBasicGraphics(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, 32, false);

	IkiShowWindow();

	UpdateWindow((HWND)IkiGetWindowHandle());

	float counter = 0.0f;

	bool horizontalMove;
	bool verticalMove;
	bool stopMovement = false;

	int snakeBodyIndex = 1;

	Snake snake[200];
	memset(snake, 0, sizeof(Snake) * 10);

	// Head
	snake[0].isHead = true;
	snake[0].color = { 81, 0, 0, 255 };
	snake[0].pos = { 2, 2 };

	horizontalMove = true;
	snake[0].direction = { 1, 0 };

	// Food
	int foodPosX = 10;
	int foodPosY = 7;

	Food food;
	memset(&food, 0, sizeof(Food));
	food.isEaten = false;
	food.color = COLOR_GREEN;
	food.pos = { foodPosX, foodPosY };

	food.rect.left = food.pos.x * ((CANVAS_WIDTH / MAP_WIDTH)) + 1;
	food.rect.top = food.pos.y *((CANVAS_WIDTH / MAP_HEIGHT)) + 1;
	food.rect.right = ((CANVAS_WIDTH / MAP_WIDTH) - 1);
	food.rect.bottom = ((CANVAS_HEIGHT / MAP_HEIGHT) - 1);

	while (IkiRunProcess())
	{
		// Input
		if (IkiKeyboardIsPressed('D'))
		{
			horizontalMove = true;
			verticalMove = false;

			snake[0].direction.x = 1;
			snake[0].direction.y = 0;
		}
		else if (IkiKeyboardIsPressed('A'))
		{
			horizontalMove = true;
			verticalMove = false;

			snake[0].direction.x = -1;
			snake[0].direction.y = 0;
		}
		else if (IkiKeyboardIsPressed('W'))
		{
			horizontalMove = false;
			verticalMove = true;

			snake[0].direction.x = 0;
			snake[0].direction.y = -1;
		}
		else if (IkiKeyboardIsPressed('S'))
		{
			horizontalMove = false;
			verticalMove = true;

			snake[0].direction.x = 0;
			snake[0].direction.y = 1;
		}
		else if (IkiKeyboardIsPressed(VK_ESCAPE))
		{
			IkiCloseWindow();
		}

		// Update
		counter += dt;
		while (counter > 0.15f)
		{
			// Update snake body
			if (!stopMovement)
			{
				for (int i = snakeBodyIndex - 1; i > 0; --i)
				{
					int previousX = snake[i - 1].pos.x;
					int previousY = snake[i - 1].pos.y;

					snake[i].pos.x = previousX;
					snake[i].pos.y = previousY;

					snake[i].rect.left = snake[i].pos.x * ((CANVAS_WIDTH / MAP_WIDTH)) + 1;
					snake[i].rect.top = snake[i].pos.y * ((CANVAS_WIDTH / MAP_HEIGHT)) + 1;
					snake[i].rect.right = ((CANVAS_WIDTH / MAP_WIDTH) - 1);
					snake[i].rect.bottom = ((CANVAS_HEIGHT / MAP_HEIGHT) - 1);
				}

				if (horizontalMove)
				{
					snake[0].pos.x += snake[0].direction.x;
				}
				else
				{
					snake[0].pos.y += snake[0].direction.y;
				}
			}

			counter = 0.0f;
		}

		if (snake[0].pos.x == food.pos.x &&
			snake[0].pos.y == food.pos.y)
		{
			food.isEaten = true;
		}

		// Check if the head hits the body
		// ...

		if (food.isEaten)
		{
			// Update food position
			std::uniform_int_distribution<> newPosX(0, MAP_WIDTH - 1);
			std::uniform_int_distribution<> newPosY(0, MAP_HEIGHT - 1);

			food.pos.x = newPosX(seed);
			food.pos.y = newPosY(seed);
			food.isEaten = false;

			food.rect.left = food.pos.x * ((CANVAS_WIDTH / MAP_WIDTH)) + 1;
			food.rect.top = food.pos.y * ((CANVAS_WIDTH / MAP_HEIGHT)) + 1;
			food.rect.right = ((CANVAS_WIDTH / MAP_WIDTH) - 1);
			food.rect.bottom = ((CANVAS_HEIGHT / MAP_HEIGHT) - 1);

			// Grow the snake
			snake[snakeBodyIndex].isBody = true;
			snake[snakeBodyIndex].color = snake[0].color;

			if (snake[snakeBodyIndex].color.b < 255)
			{
				snake[snakeBodyIndex].color.b += (snakeBodyIndex + 20);
			}
			else
			{
				snake[snakeBodyIndex].color.g += 1;
				snake[snakeBodyIndex].color.r += 1;
			}

			snake[snakeBodyIndex].pos = snake[snakeBodyIndex - 1].pos;
			snakeBodyIndex += 1;
		}

		RECT rect = { 0 };
		rect.left = snake[0].pos.x * ((CANVAS_WIDTH / MAP_WIDTH)) + 1;
		rect.top = snake[0].pos.y * ((CANVAS_WIDTH / MAP_HEIGHT)) + 1;
		rect.right = ((CANVAS_WIDTH / MAP_WIDTH) - 1);
		rect.bottom = ((CANVAS_HEIGHT / MAP_HEIGHT) - 1);

		snake[0].rect = rect;

		int headRight = snake[0].rect.left + snake[0].rect.right;
		if (headRight >= CANVAS_WIDTH)
		{
			stopMovement = true;
		}


		IkiRenderStart();
		IkiClearBackground(COLOR_GRAY);

		// Draw
		for (int y = 1; y < MAP_HEIGHT; ++y)
		{
			float map = (float)CANVAS_HEIGHT / (float)MAP_HEIGHT;
			float height = map * y;

			DrawLine(1.0f, height, (float)CANVAS_WIDTH - 1.0f, height, COLOR_BLACK);
		}

		for (int x = 1; x < MAP_WIDTH; ++x)
		{
			float map = (float)CANVAS_WIDTH / (float)MAP_WIDTH;
			float width = map * x;

			DrawLine(width, 1.0f, width, (float)CANVAS_HEIGHT - 1.0f, COLOR_BLACK);
		}

		if (!food.isEaten)
		{
			DrawRect(food.rect, food.color);
		}

		for (int i = 1; i < snakeBodyIndex; ++i)
		{
			DrawRect(snake[i].rect, snake[i].color);
		}

		DrawRect(snake[0].rect, snake[0].color);

		IkiRenderEnd();


		// Time stuff
		endTime = IkiGetPerformanceCounter();
		elapsedTime = endTime - startTime;
		elapsedTime *= 1000000; // Converts to microseconds to guard againts loss-of-precision
		elapsedTime /= frequency; // (microseconds per frame)

		float millisecondsPerFrame = elapsedTime * (1.0f / 1000.0f);
		float secondsPerFrame = millisecondsPerFrame * (1.0f / 1000.0f);

		dt = secondsPerFrame;

		startTime = endTime;

		Sleep(1);
	}


	return 0;
}
#endif