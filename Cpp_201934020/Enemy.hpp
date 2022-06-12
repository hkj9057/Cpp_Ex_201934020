#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace JunSeok_Game
{
	class Enemy
	{
	public:
		float XPoint;
		float YPoint;
		float Enemy_Speed;

		Enemy()
		{
			XPoint = 0.9f;
			YPoint = 0.85f;
			Enemy_Speed = (float)(rand() % 10) / 1000 + 0.005f;
		}
		~Enemy()
		{}

		void EnemyMove()
		{
			XPoint -= Enemy_Speed;
			if (XPoint < -1.0f) XPoint = 0.9f;
		}
		void EnemyInitialize()
		{
			XPoint = 0.9f;
			YPoint = 0.85f;
			Enemy_Speed = (float)(rand() % 10) / 1000 + 0.005f;
		}

	};

}
