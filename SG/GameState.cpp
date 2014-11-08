#include "GameState.h"
#include "PlayableUnit.h"
#include "GameTime.h"
#include "SceneObject.h"
#include "Word.h"
#include "Words.h"
#include "WordHandler.h"
#include "Ground.h"
#include "misc.h"
#include <list>

using namespace std;
using namespace DirectX;

namespace GameState
{
	namespace
	{
		PlayableUnit* Player;
		GameTime* GameTimer;
		WordHandler* WHandler;
		Ground* DirtGround;

		list<GameObject*> GameObjects;
		list<SceneObject*> SceneObjects;

		bool UpKey;
		bool DownKey;
		bool LeftKey;
		bool RightKey;

		float CheckCollision(Collideable* obj1, Collideable* obj2, XMFLOAT2 dir)
		{
			XMFLOAT2 bl(D3D11_FLOAT32_MAX, D3D11_FLOAT32_MAX);
			XMFLOAT2 br(3.4e-37f, D3D11_FLOAT32_MAX);

			auto b1 = obj1->getBounds();
			auto b2 = obj2->getBounds();

			for (auto iter = b1.begin(); iter != b1.end(); iter++)
			{
				if (iter->x < bl.x)
					bl.x = iter->x;
				if (iter->x > br.x)
					br.x = iter->x;
				if (iter->y < bl.y)
					br.y = bl.y = iter->y;
			}

			auto t1 = obj1->m_transform;
			auto t2 = obj2->m_transform;

			bl.x += t1.x;
			br.x += t1.x;
			bl.y += t1.y;
			br.y += t1.y;

			float dy = dir.y;

			for (auto iter = b2.begin(); iter != b2.end(); iter++)
			{
				if (iter->y + t2.y >= bl.y)
				{
					return (iter->y + t2.y - bl.y);
				}
			}

			return dy;
		}
	}

	void Initialize()
	{
		GameTimer = new GameTime();
		WHandler = new WordHandler();
		DirtGround = new Ground(-200, -200);

		WHandler->addWord(new Strength());

		Player = new PlayableUnit(10, 1, 1, L"player1");

		GameObjects.clear();

		UpKey = false;
		DownKey = false;
		LeftKey = false;
		RightKey = false;
	}

	void Update()
	{
		const float MOVE_AMT = 10;

		GameTimer->update();
		float tt = GameTimer->getTotalTime() * SEC_TO_TICK;
		float dt = GameTimer->getElapsedTime() * SEC_TO_TICK;

		if (UpKey)
			Player->move(0, dt * MOVE_AMT, 0);
		if (DownKey)
		{
			float dm = CheckCollision(Player, DirtGround, XMFLOAT2(0, -dt * MOVE_AMT));
			Player->move(0, dm, 0);
		}
		if (LeftKey)
			Player->move(-dt * MOVE_AMT, 0, 0);
		if (RightKey)
			Player->move(dt * MOVE_AMT, 0, 0);

		Player->action(tt, dt);

		auto iter = GameObjects.begin();
		while (iter != GameObjects.end())
		{
			(*iter)->action(tt, dt);
			iter++;
		}

		auto iter2 = SceneObjects.begin();
		while (iter2 != SceneObjects.end())
		{
			(*iter2)->update(tt, dt);
			iter2++;
		}
	}

	void CleanUp()
	{
		delete Player;
		delete WHandler;
		delete GameTimer;

		auto iter = GameObjects.begin();
		while (iter != GameObjects.end())
		{
			delete (*iter);
			iter++;
		}
	}

	void AddGameObject(GameObject* obj)
	{
		GameObjects.push_back(obj);
	}

	void AddSceneObject(SceneObject* obj)
	{
		SceneObjects.push_back(obj);
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