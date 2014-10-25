#include "GameState.h"
#include "Background.h"
#include "PlayableUnit.h"
#include "GameTime.h"
#include "Word.h"
#include "Words.h"
#include "WordHandler.h"

namespace GameState
{
	namespace
	{
		PlayableUnit* Player;
		Background* Scenery;
		GameTime* GameTimer;
		WordHandler* WHandler;

		bool UpKey;
		bool DownKey;
		bool LeftKey;
		bool RightKey;
	}

	void Initialize()
	{
		GameTimer = new GameTime();
		WHandler = new WordHandler();

		WHandler->addWord(new Strength());

		Scenery = new Background(-400, -300, 800, 600, L"background.png");
		Player = new PlayableUnit(10, 1, 1, L"player1");

		UpKey = false;
		DownKey = false;
		LeftKey = false;
		RightKey = false;
	}

	void Update()
	{
		const float MOVE_AMT = 100;

		GameTimer->update();
		float dt = GameTimer->getElapsedTime();

		if (UpKey)
			Player->move(0, dt * MOVE_AMT, 0);
		if (DownKey)
			Player->move(0, -dt * MOVE_AMT, 0);
		if (LeftKey)
			Player->move(-dt * MOVE_AMT, 0, 0);
		if (RightKey)
			Player->move(dt * MOVE_AMT, 0, 0);
	}

	void CleanUp()
	{
		delete Scenery;
		delete Player;
		delete WHandler;
		delete GameTimer;
	}

	void HandleInput(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_UP:
				UpKey = true; break;
			case VK_DOWN:
				DownKey = true; break;
			case VK_LEFT:
				LeftKey = true; break;
			case VK_RIGHT:
				RightKey = true; break;
			} break;
		case WM_KEYUP:
			switch (wParam)
			{
			case VK_UP:
				UpKey = false; break;
			case VK_DOWN:
				DownKey = false; break;
			case VK_LEFT:
				LeftKey = false; break;
			case VK_RIGHT:
				RightKey = false; break;
			} break;
		case WM_CHAR:
			Word* word = WHandler->nextChar(wParam);
			if (word)
				word->action();
			break;
		}
	}
}