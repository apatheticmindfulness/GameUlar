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

		//Sleep(1);
	}

	game.End();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif


	return 0;
}