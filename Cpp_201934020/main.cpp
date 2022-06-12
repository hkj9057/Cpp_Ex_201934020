#define _CRT_SECURE_NO_WARNINGS
#include "JGameLoop.hpp"

void main()
{
	JunSeok_Game::JGameLoop JGameLoop;
	srand(time(NULL));
	JGameLoop.GlRun();

	_CrtDumpMemoryLeaks();
}
