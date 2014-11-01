#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <Windows.h>

class GameObject;

namespace GameState
{
	void Initialize();
	void Update();
	void CleanUp();

	void AddGameObject(GameObject* obj);

	void HandleInput(UINT message, WPARAM wParam, LPARAM lParam);
}

#endif // GAMESTATE_H