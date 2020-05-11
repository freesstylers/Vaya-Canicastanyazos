#include "GameManager.h"
#include "MotorCasaPaco.h"
#include <sstream>
#include <fstream>
#include "Scene/SceneManager.h"
GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{

}

GameManager::GameManager() : Component("GameManager") {
	EventManager::getInstance()->RegisterListener(this, "finNivel");
	EventManager::getInstance()->RegisterListener(this, "changeScene");
	readData();
}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
		instance->readData();
	}

	return instance;
}
void GameManager::clean()
{
	delete instance;
}

bool GameManager::ReceiveEvent(Event& event)
{
	if (event.type == "finNivel")
		saveData(SceneManager::getInstance()->getCurrentScene()->getName());
	if (event.type == "changeScene")
	{
		time = MotorCasaPaco::getInstance()->getTime();
	}
	return true;
}
int GameManager::getStars()
{
	return stars_;
}

void GameManager::addStars(int s)
{
	stars_ += s;
}

void GameManager::resetStars()
{
	stars_ = 0;
}
void GameManager::saveData(std::string name)
{

	if (levels.find(name) != levels.end())
	{
		if(levels.find(name)->second.stars < stars_)
			levels.find(name)->second.stars = stars_;

		levels.find(name)->second.time = MotorCasaPaco::getInstance()->getTimeDifference(time);
	}
	else
	{
		LevelInfo lev;
		lev.stars = stars_;
		lev.time = MotorCasaPaco::getInstance()->getTimeDifference(time);
		levels.insert(std::pair<std::string, LevelInfo>(name, lev));
	}

	std::ofstream data;
	data.open("assets/saves/saveData");
	if (data.is_open())
	{
		for (auto it : levels)
		{
			data << it.first << " ";
			data << it.second.stars << " ";
			data << std::to_string(it.second.time) << "\n";
		}
	}
	std::cout << "Stars: " << levels.find(name)->second.stars << " Time: " << levels.find(name)->second.time << std::endl;
	stars_ = 0;
	time = 0;
	data.close();
}

void GameManager::readData()
{
	std::ifstream data;
	data.open("assets/saves/saveData");
	if (data.is_open())
	{
		while (!data.eof())
		{
			std::string name;
			int stars;
			float time;
			while (data >> name >> stars >> time)
			{
				LevelInfo lev;
				lev.stars = stars;
				lev.time = time;
				levels.insert(std::pair<std::string, LevelInfo>(name, lev));
			}
		}
	}
	data.close();
}
