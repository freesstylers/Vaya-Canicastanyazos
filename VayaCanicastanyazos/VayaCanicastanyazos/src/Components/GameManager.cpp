#include "GameManager.h"
#include "MotorCasaPaco.h"
#include <sstream>
#include <fstream>
#include "Scene/SceneManager.h"
#include "GUI/GUI_Manager.h"

GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{

}

GameManager::GameManager() : Component("GameManager") {
	EventManager::getInstance()->RegisterListener(this, "inicioNivel");
	EventManager::getInstance()->RegisterListener(this, "estrellaCogida");
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

void GameManager::pause()
{
	MotorCasaPaco::getInstance()->pause();
	paused_ = !paused_;

	//Mensaje?
}

bool GameManager::isPaused()
{
	return paused_;
}

void GameManager::update()
{
	if (inLevel_) //Está en nivel
	{
		std::cout << "ee\n";
		//Actualizar tiempo
	}
}

bool GameManager::ReceiveEvent(Event& event)
{
	if (event.type == "inicioNivel")
	{
		inLevel_ = true;
	}
	if (event.type == "finNivel")
	{	
		inLevel_ = false;
		saveData(SceneManager::getInstance()->getCurrentScene()->getName());
	}
	if (event.type == "changeScene")
	{
		time = MotorCasaPaco::getInstance()->getTime();
	}
	if (event.type == "estrellaCogida")
	{
		int stars = GameManager::getInstance()->getStars();

		switch (stars)
		{
		case 1:
			GUI_Manager::getInstance()->changeImage("Ingame/Colleccionable_1", "VayaCanicastanhazos/Star_Yes");
			break;
		case 2:
			GUI_Manager::getInstance()->changeImage("Ingame/Colleccionable_2", "VayaCanicastanhazos/Star_Yes");
			break;
		case 3:
			GUI_Manager::getInstance()->changeImage("Ingame/Colleccionable_3", "VayaCanicastanhazos/Star_Yes");
			break;
		}
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
			std::string number;
			int stars;
			float time;
			while (data >> name >> number >> stars >> time)
			{
				LevelInfo lev;
				lev.stars = stars;
				lev.time = time;
				name += " " + number;
				levels.insert(std::pair<std::string, LevelInfo>(name, lev));
			}
		}
	}
	data.close();
}

std::map<std::string, LevelInfo> GameManager::getLevels()
{
	return levels;
}
