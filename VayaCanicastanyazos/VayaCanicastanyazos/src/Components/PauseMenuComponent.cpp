#include "PauseMenuComponent.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"

PauseMenuComponent::PauseMenuComponent(json& args): Component(args)
{

}

PauseMenuComponent::~PauseMenuComponent()
{
	Component::~Component();
}

bool PauseMenuComponent::ReceiveEvent(Event& event)
{
	return true;
}

bool PauseMenuComponent::functionReturn(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...
	return true;
}

bool PauseMenuComponent::functionReset(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(level);
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool PauseMenuComponent::functionSettings(const CEGUI::EventArgs& e)
{
	//vainas de layouts
	return true;
}

bool PauseMenuComponent::functionMainMenu(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(mainMenu);
	MotorCasaPaco::getInstance()->pause();
	EventManager::getInstance()->EmitEvent("finNivel");
	return true;
}

bool PauseMenuComponent::functionExit(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->exit();
	return true;
}

void PauseMenuComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delayPause)
	{
		if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
		{
			MotorCasaPaco::getInstance()->pause();

			MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, true); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...

			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
	}
}

void PauseMenuComponent::pausedUpdate()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
		{
			if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delayPause)
			{
				MotorCasaPaco::getInstance()->pause();

				MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...

				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
		}

		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::	CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
		{
			if (currenPos > 0)
				currenPos--;
			else
				currenPos = tam - 1;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(x, positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}

		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
		{
			if (currenPos < (tam - 1))
				currenPos++;
			else
				currenPos = 0;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(x, positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}

		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
	}
}

void PauseMenuComponent::init(json& j)
{
	if (!j["delayPause"].is_null() && !j["delay"].is_null() && !j["buttons"].is_null() && j["buttons"].is_array())
	{
		std::vector<std::string> vec = j["buttons"];

		int count = 0;
		for (std::string name : vec) {

			if (count == 0)
				x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			
			float y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

			positionsY.push_back(y);

			switch (count)
			{
			case 0:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionReturn, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 1:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionReset, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 2:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionSettings, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 3:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionMainMenu, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 4:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionExit, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			}

			count++;
		}

		tam = count;

		std::string interm = j["Level"];
		level = interm;

		std::string interm2 = j["MainMenu"];
		mainMenu = interm2;

		delay = j["delay"];
		delayPause = j["delayPause"];
		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(x, positionsY[currenPos]);
		currentTime = MotorCasaPaco::getInstance()->getTime();
	}
}
