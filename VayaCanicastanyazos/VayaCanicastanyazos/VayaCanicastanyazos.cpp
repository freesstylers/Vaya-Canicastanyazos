#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "Scene/JsonFactoryParser.h"
#include "src/Components/CameraController.h"
#include "src/Components/RotateWorld.h";
#include "src/Components/SimpleMovement.h"
#include "src/Components/ChangeSceneButtonComponent.h"
#include "src/Components/ExitButtonComponent.h"

MotorCasaPaco* motorCasaPaco;

//-----------------------------Factories-----------------------------------------
class RotateWorldFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RotateWorld(args);
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

/*class CameraControllerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new CameraController(args);
	};
};*/

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
	catch (const std::exception& e)
	{
		throw std::runtime_error("Motor Casa Paco init fail \n" + std::string(e.what()) + "\n");	return 0;
	}

	motorCasaPaco = MotorCasaPaco::getInstance();

	try
	{
		motorCasaPaco->init();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		delete motorCasaPaco;
		return 0;
	}

	JsonFactoryParser::getInstance()->addFactory("RotateWorld", new RotateWorldFactory());
	JsonFactoryParser::getInstance()->addFactory("SimpleMovement", new SimpleMovementFactory());
	//JsonFactoryParser::getInstance()->addFactory("CameraController", new CameraControllerFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());

	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("VayaCanicastanhazos.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("GWEN.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("VayaCanicastanhazos/Mouse_Arrow");
	//motorCasaPaco->changeScene("Menu");

	motorCasaPaco->changeScene("Menu");

	motorCasaPaco->start();

	delete motorCasaPaco;

	return 0;
}