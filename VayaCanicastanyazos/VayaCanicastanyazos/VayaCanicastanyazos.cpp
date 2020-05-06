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

#include "Components/ChangeFullScreenComponent.h"
#include "Components/FormatResolutionChangeComponent.h"
#include "Components/ApplyGraphicChangesComponent.h"
#include "Components/ChangeVyncComponent.h"
#include "Components/FSAAChangeComponent.h"
#include "Components/ShadowsChangeComponent.h"
#include "Components/ApplyAdvancedGraphicChangesComponent.h"
#include "Components/RevertGraphicChangesComponent.h"

#include "Components/RevertAdvancedGraphicChangesComponent.h"
#include "Components/ChangeGammaComponent.h"
#include "Components/ChangeGraphicSceneComponent.h"
#include "Components/StarCollision.h"

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

class ChangeFullScreenComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeFullScreenComponent(args);
	};
};

class FormatResolutionChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FormatResolutionChangeComponent(args);
	};
};

class ApplyGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyGraphicChangesComponent(args);
	};
};

class ChangeVSyncComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeVSyncComponent(args);
	};
};

class FSAAChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FSAAChangeComponent(args);
	};
};

class ShadowsChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ShadowsChangeComponent(args);
	};
};

class ApplyAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyAdvancedGraphicChangesComponent(args);
	};
};

class RevertGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertGraphicChangesComponent(args);
	};
};

class RevertAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertAdvancedGraphicChangesComponent(args);
	};
};

class ChangeGammaComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGammaComponent(args);
	};
};

class ChangeGraphicSceneComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGraphicSceneComponent(args);
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

	JsonFactoryParser::getInstance()->addFactory("FakeRotation", new FakeRotationFactory());
	JsonFactoryParser::getInstance()->addFactory("SimpleMovement", new SimpleMovementFactory());
	JsonFactoryParser::getInstance()->addFactory("CameraController", new CameraControllerFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeFullScreenComponent", new ChangeFullScreenComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("FormatResolutionChangeComponent", new FormatResolutionChangeComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ApplyGraphicChangesComponent", new ApplyGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeVSyncComponent", new ChangeVSyncComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("FSAAChangeComponent", new FSAAChangeComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ShadowsChangeComponent", new ShadowsChangeComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ApplyAdvancedGraphicChangesComponent", new ApplyAdvancedGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("RevertGraphicChangesComponent", new RevertGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("RevertAdvancedGraphicChangesComponent", new RevertAdvancedGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeGammaComponent", new ChangeGammaComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeGraphicSceneComponent", new ChangeGraphicSceneComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("StarCollision", new StarCollisionFactory());

	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("VayaCanicastanhazos.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("VayaCanicastanhazos/Mouse_Arrow");

	motorCasaPaco->start("Menu");

	delete motorCasaPaco;

	return 0;
}