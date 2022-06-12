#pragma once
#include <Windows.h>

namespace JunSeok_Game
{
	class Player
	{
	public:
		float XPoint;
		float YPoint;
		Player()
		{
			XPoint = 0.0f;
			YPoint = 0.0f;
		}
		~Player()
		{}
		void isKeyPressed()
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8001)
			{
				XPoint -= 0.009;
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8001)
			{
				XPoint += 0.009;
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001)
			{
				YPoint += 0.009;
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
			{
				YPoint -= 0.009;
			}
		}
		void PlayerInitialize()
		{
			XPoint = 0.0f;
			YPoint = 0.0f;
		}
	};
}
