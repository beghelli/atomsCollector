#include "Core.h"
#include "MyGame.h"

using namespace Engine;

int main(int argc, char *argv[])
{
	MyGame* game = new MyGame();
	Core* engineCore = new Core(game);

	return engineCore->run();
}
