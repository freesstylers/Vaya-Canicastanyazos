#include "GameManager.h"

GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{

}

GameManager::GameManager() : Component("GameManager") {

}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
		instance = new GameManager();

	return instance;
}


void GameManager::clean()
{
	delete instance;
}

int GameManager::getStars()
{
	return stars_;
}

void GameManager::addStars(int s)
{
	stars_ += s;
}
