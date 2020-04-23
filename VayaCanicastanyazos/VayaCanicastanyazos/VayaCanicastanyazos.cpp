#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "Scene/JsonFactoryParser.h"
#include "RotateWorld.h";
#include "SimpleMovement.h"
#include "CameraController.h"
MotorCasaPaco* motorCasaPaco;

#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{

	try { MotorCasaPaco::setupInstance("Motor Casa Paco"); }
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

	class CameraControllerFactory : public BaseFactory
	{
	public:
		Component* createComponent(json& args) override
		{
			return new CameraController(args);
		};
	};
//--------------------------------------------------------------------------------

	JsonFactoryParser::getInstance()->addFactory("RotateWorld", new RotateWorldFactory());
	JsonFactoryParser::getInstance()->addFactory("SimpleMovement", new SimpleMovementFactory());
	JsonFactoryParser::getInstance()->addFactory("CameraController", new CameraControllerFactory());
	motorCasaPaco->changeScene("nivel2");

	motorCasaPaco->start();

	delete motorCasaPaco;

	return 0;
}