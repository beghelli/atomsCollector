#include <iostream>
#include "Game.h"
#include "GameScene.h"

bool Engine::Game::loadScene(GameScene* gameScene)
{
	status = Game::STATUS_LOADING;
	auto loader = [&, gameScene](EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository) -> void
	{
		status = gameScene->load(entityRepository, UIEntityRepository);
		currentGameScene = gameScene;
	};
	loadingQueue.push_back(loader);
	return true;
}
