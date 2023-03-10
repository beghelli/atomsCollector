#include "Engine.h"
#include "MyGame.h"

int main(int argc, char *argv[])
{
	MyGame* game = new MyGame();
	Engine* engine = new Engine(game);

	return engine->run();
}
