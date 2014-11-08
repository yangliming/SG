#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <Windows.h>

class GameObject;
class SceneObject;

namespace GameState
{
	void Initialize();
	void Update();
	void CleanUp();

	void AddGameObject(GameObject* obj);
	void AddSceneObject(SceneObject* obj);

	void HandleInput(UINT message, WPARAM wParam, LPARAM lParam);
}

#endif // GAMESTATE_H