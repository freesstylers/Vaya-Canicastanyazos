#include "Components/LevelSelectionComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"

LevelSelectionComponent::LevelSelectionComponent(json& args): Component(args)
{

}

LevelSelectionComponent::~LevelSelectionComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool LevelSelectionComponent::functionLoader1(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[0]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader2(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[1]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader3(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[2]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader4(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[3]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader5(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[4]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader6(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[5]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader7(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[6]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLoader8(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[7]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool LevelSelectionComponent::functionLeftArrow(const CEGUI::EventArgs& e)
{
	if (currentShow == 0)
	{
		levels = { "nivel 9", "nivel 10", "nivel 11", "nivel 12", "nivel 13", "nivel 14", "nivel 15", "nivel 16" };
		currentShow = 1;
	}

	else if (currentShow == 1)
	{
		levels = { "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 6", "nivel 7", "nivel 8" };
		currentShow = 0;
	}

	updateTexts(currentShow);

	return true;
}

bool LevelSelectionComponent::functionRightArrow(const CEGUI::EventArgs& e)
{
	if (currentShow == 0)
	{
		levels = { "nivel 9", "nivel 10", "nivel 11", "nivel 12", "nivel 13", "nivel 14", "nivel 15", "nivel 16" };
		currentShow = 1;
	}

	else if (currentShow == 1)
	{
		levels = { "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 6", "nivel 7", "nivel 8" };
		currentShow = 0;
	}

	updateTexts(currentShow);

	return true;
}

bool LevelSelectionComponent::ReceiveEvent(Event& event)
{
	return true;
}

void LevelSelectionComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
		{
			/*if (currenPos < (tam - 1))
				currenPos++;
			else
				currenPos = 0;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();*/
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
		{
			/*if (currenPos > 0)
				currenPos--;
			else
				currenPos = tam - 1;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();*/
		}
	}

		//Boton A
		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
}

void LevelSelectionComponent::assignFunctions(int num, std::string name)
{
	switch (num)
	{
		case 0:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader1, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 1:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader2, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 2:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader3, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 3:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader4, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 4:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader5, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 5:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader6, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 6:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader7, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
		case 7:
		{
			auto helperFunction = std::bind(&LevelSelectionComponent::functionLoader8, this, std::placeholders::_1);
			GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
		}
		break;
	}
}

void LevelSelectionComponent::updateTexts(int num)
{
	int i = 0;

	for (CEGUI::Window* w : texts)
	{
		GUI_Manager::getInstance()->changeText(w, levels[i]);
		i++;
	}
}

void LevelSelectionComponent::init(json& j)
{
	//if (!j["topButtons"].is_null() && j["topButtons"].is_array() && !j["botButtons"].is_null() && j["botButtons"].is_array() && !j["leftArrow"].is_null() && !j["rightArrow"].is_null() && !j["delay"].is_null())
	{
		float x;
		float y;

		std::vector<std::string> vec = j["topButtons"];
		
		int count = 0;
		
		for (std::string name : vec) {

			x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();
			
			positionsXTop.push_back(x);
			positionsYTop.push_back(y);

			assignFunctions(count, name);

			texts.push_back(MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getWindowElement());

			count++;
		}

		std::vector<std::string> vec2 = j["botButtons"];

		for (std::string name : vec2) {

			x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

			positionsXBot.push_back(x);
			positionsYBot.push_back(y);

			assignFunctions(count, name);

			texts.push_back(MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getWindowElement());

			count++;
		}



		xLeftArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["leftArrow"]).getCenterPointXAbsolute();
		yLeftArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["leftArrow"]).getCenterPointXAbsolute();

		auto helperFunction = std::bind(&LevelSelectionComponent::functionLeftArrow, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["leftArrow"]), helperFunction);

		xRightArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["rightArrow"]).getCenterPointXAbsolute();
		yRightArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["rightArrow"]).getCenterPointXAbsolute();

		auto helperFunction1 = std::bind(&LevelSelectionComponent::functionRightArrow, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["rightArrow"]), helperFunction1);

		delay = j["delay"];
		currentTime = MotorCasaPaco::getInstance()->getTime();
		
		currentShow = 0;
		levels = { "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 6", "nivel 7", "nivel 8" };

		updateTexts(currentShow);
		//std::cout << tam << "\n";
		//posX = MotorCasaPaco::getInstance()->getScreenWidth() / 2;
		//posY = MotorCasaPaco::getInstance()->getScreenHeight() / 2;

		//MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);*/
	}
}
