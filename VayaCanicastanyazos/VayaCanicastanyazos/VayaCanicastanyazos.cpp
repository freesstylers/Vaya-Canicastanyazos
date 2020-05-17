#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "Scene/JsonFactoryParser.h"
#include "Components/CameraController.h"
#include "Components/FakeRotation.h";
#include "Components/SimpleMovement.h"
#include "Components/ChangeSceneButtonComponent.h"
#include "Components/ExitButtonComponent.h"
#include "Components/StarCollision.h"

#include "Components/DeathZoneComponent.h"
#include "Components/GoalComponent.h"
#include "Components/GameManager.h"

#include "Components/PauseMenuComponent.h"
#include "Components/OptionsMenuComponent.h"
#include "Components/MainMenuInputComponent.h"
#include "Components/LevelSelectionComponent.h"

MotorCasaPaco* motorCasaPaco;

//-----------------------------Factories-----------------------------------------
class FakeRotationFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FakeRotation(args);
	};
};

class SimpleMovementFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new SimpleMovement(args);
	};
};

class CameraControllerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new CameraController(args);
	};
};

class ChangeSceneButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeSceneButtonComponent(args);
	};
};

class ExitButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ExitButtonComponent(args);
	};
};

class DeathZoneComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new DeathZoneComponent(args);
	};
};

class StarCollisionFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new StarCollision(args);
	};
};

class GoalComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new GoalComponent(args);
	};
};

class PauseMenuComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new PauseMenuComponent(args);
	};
};

class OptionsMenuComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new OptionsMenuComponent(args);
	};
};

class MainMenuInputComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MainMenuInputComponent(args);
	};
};

class LevelSelectionComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new LevelSelectionComponent(args);
	};
};

class GameManagerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return GameManager::getInstance();
	};
};

//--------------------------------------------------------------------------------


#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{

	try { MotorCasaPaco::setupInstance("Vaya Canicastanhazos"); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("Motor Casa Paco init fail \n" + std::string(e.what()) + "\n");	return 0;
	}

	motorCasaPaco = MotorCasaPaco::getInstance();

	try
	{
		motorCasaPaco->init();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << "\n";
		delete motorCasaPaco;
		return 0;
	}

	JsonFactoryParser::getInstance()->addFactory("FakeRotation", new FakeRotationFactory());
	JsonFactoryParser::getInstance()->addFactory("SimpleMovement", new SimpleMovementFactory());
	JsonFactoryParser::getInstance()->addFactory("CameraController", new CameraControllerFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("DeathZoneComponent", new DeathZoneComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("GoalComponent", new GoalComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("StarCollision", new StarCollisionFactory());
	JsonFactoryParser::getInstance()->addFactory("PauseMenuComponent", new PauseMenuComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("OptionsMenuComponent", new OptionsMenuComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("MainMenuInputComponent", new MainMenuInputComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("LevelSelectionComponent", new LevelSelectionComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("GameManager", new GameManagerFactory());

	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("VayaCanicastanhazos.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("VayaCanicastanhazos/Mouse_Arrow");

	motorCasaPaco->start("Menu");

	delete motorCasaPaco;

	return 0;
}