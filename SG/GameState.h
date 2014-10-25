#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <Windows.h>

namespace GameState
{
	void Initialize();
	void Update();
	void CleanUp();

	void HandleInput(UINT message, WPARAM wParam, LPARAM lParam);
}

#endif // GAMESTATE_H