#include "Components/LevelSelectionComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"
#include "Components/GameManager.h"
#include "Scene/SceneManager.h"
#include "Graphics/Mesh.h"

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
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader2(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[1]);	
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader3(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[2]);	
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader4(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[3]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader5(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[4]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader6(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[5]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader7(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[6]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLoader8(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levels[7]);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Ingame_Music.mp3", 2, true);
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool LevelSelectionComponent::functionLeftArrow(const CEGUI::EventArgs& e)
{
	if (currentShow == 0)
	{
		levels = { "nivel 10", "nivel 11", "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 7" };
		currentShow = 1;
	}

	else if (currentShow == 1)
	{
		levels = { "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 7", "nivel 8", "nivel 9" };
		currentShow = 0;
	}

	updateTexts(currentShow);

	return true;
}

bool LevelSelectionComponent::functionRightArrow(const CEGUI::EventArgs& e)
{
	if (currentShow == 0)
	{
		levels = { "nivel 10", "nivel 11", "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 7" };
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
		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
		{
			if (leftArrow)
			{
				leftArrow = false;
				rightArrow = true;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xRightArrow, yRightArrow);
			}
			else if (rightArrow)
			{
				rightArrow = false;
				posX = positionsX.size() - 1;
				posY = 0;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
			}
			else
			{
				if (posX == 0)
				{
					leftArrow = true;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xLeftArrow, yLeftArrow);
				}
				else
				{
					posX--;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
				}
			}

			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
		{
			if (leftArrow)
			{
				leftArrow = false;
				posX = 0;
				posY = 0;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
			}
			else if (rightArrow)
			{
				rightArrow = false;
				leftArrow = true;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xLeftArrow, yLeftArrow);
			}
			else
			{
				if (posX < positionsX.size() - 1)
				{
					posX++;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
				}
				else
				{
					rightArrow = true;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xRightArrow, yRightArrow);
				}
			}

			currentTime = MotorCasaPaco::getInstance()->getTime();
		}


		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
		{
			if (!leftArrow && !rightArrow)
			{
				if (extra)
				{
					extra = false;
					posY = 0;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
				}
				else
				{
					if (posY == 1)
					{
						extra = true;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtraButton, yExtraButton);	//Extra
					}
					else
					{
						posY = 1;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
					}
				}
			}

			currentTime = MotorCasaPaco::getInstance()->getTime();
		}

		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
		{
			if (!leftArrow && !rightArrow)
			{
				if (extra)
				{
					extra = false;
					posY = 1;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
				}
				else
				{
					if (posY == 1)
					{
						posY = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
					}
					else
					{
						extra = true;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtraButton, yExtraButton);	//Extra
					}
				}
			}

			currentTime = MotorCasaPaco::getInstance()->getTime();
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

void LevelSelectionComponent::storeTexts()
{
	std::map <std::string, LevelInfo> levels_ = GameManager::getInstance()->getLevels();

	for (auto it = levels_.begin(); it != levels_.end(); it++)
	{
		std::string name = it->first;
		std::size_t position = name.find(" ");      
		std::string levelNumber = name.substr(position);

		int pos = std::stoi(levelNumber) - 1;
		int level = std::stoi(levelNumber);

		int time = it->second.time;

		int min = 0, sec = 0;
		std::string ret;

		min = time / 60;
		sec = (int)time % 60;

		std::string mins = std::to_string(min);
		if (min < 10) mins = std::string("0") + mins;

		std::string secs = std::to_string(sec);
		if (sec < 10) secs = std::string("0") + secs;

		ret = mins + std::string(":") + secs;

		recordsText[pos] = ret;
	}

	for (int i = 1; i < 9; i++)
	{
		std::string str = "LevelSelection/Info_" + std::to_string(i) + "_Star_";

		for (int k = 1; k <= 3; k++)
		{
			GUI_Manager::getInstance()->changeImage(str + std::to_string(k), "VayaCanicastanhazos/Star_No");
		}
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

	//records stuff
	std::map <std::string, LevelInfo> levels_ = GameManager::getInstance()->getLevels();

	storeTexts();

	if (currentShow == 0)
	{
		std::map <std::string, LevelInfo> levels_ = GameManager::getInstance()->getLevels();

		for (auto it = levels_.begin(); it != levels_.end(); it++) //Stars
		{
			std::string name = it->first;
			std::size_t position = name.find(" ");
			std::string levelNumber = name.substr(position);
			int level = std::stoi(levelNumber);

			levelNumber.erase(levelNumber.begin());


			if (level < 9)
			{
				int stars = it->second.stars;

				std::string str = "LevelSelection/Info_" + levelNumber + "_Star_";

				for (int k = 1; k <= stars; k++)
				{
					GUI_Manager::getInstance()->changeImage(str + std::to_string(k), "VayaCanicastanhazos/Star_Yes");
				}
			}
		}

		//Texts
		for (int j = 0; j < 8; j++)
		{
			if (recordsText[j] != "")
				GUI_Manager::getInstance()->changeText(records[j], recordsText[j]);
			else
				GUI_Manager::getInstance()->changeText(records[j], "--:--");
		}

		//Miniaturas
		
		for (int k = 1; k < 9; k++)
		{
			if (minis1far)
			{

				//Estos cerca
				std::string ent2 = "mini_" + std::to_string(k);

				Vector3 pos2 = MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent2)->getTransform()->getPosition();

				MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent2)->getTransform()->setPosition(Vector3(pos2.X, pos2.Y - 200, pos2.Z));

				if (k == 8)
					minis1far = false;
			}

			std::string ent = "mini_" + std::to_string(k + 8);

			//Vector3 pos = MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent)->getTransform()->getPosition();

			//MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent)->getTransform()->setPosition(Vector3(pos.X, pos.Y + 200, pos.Z));

			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntity(ent)->setEnabled(false);
			//MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntity(ent)->getComponent<Mesh>("Mesh")->setEnabled(false);
		}
		

	}

	else if (currentShow == 1)
	{
		std::map <std::string, LevelInfo> levels_ = GameManager::getInstance()->getLevels();

		for (auto it = levels_.begin(); it != levels_.end(); it++) //Stars
		{
			std::string name = it->first;
			std::size_t position = name.find(" ");
			std::string levelNumber = name.substr(position);

			int level = std::stoi(levelNumber) - 8;

			levelNumber.erase(levelNumber.begin());


			if (level > 8)
			{
				int stars = it->second.stars;

				std::string str = "LevelSelection/Info_" + std::to_string(level) + "_Star_";

				for (int k = 1; k <= stars; k++)
				{
					GUI_Manager::getInstance()->changeImage(str + std::to_string(k), "VayaCanicastanhazos/Star_Yes");
				}
			}
		}

		//Texts
		for (int j = 0; j < 8; j++)
		{
			if (recordsText[j+8] != "")
				GUI_Manager::getInstance()->changeText(records[j], recordsText[j+8]);
			else
				GUI_Manager::getInstance()->changeText(records[j], "--:--");
		}

		//Miniaturas
		
		for (int k = 1; k < 9; k++)
		{
			//Estos lejos

			std::string ent = "mini_" + std::to_string(k + 8);

			Vector3 pos = MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent)->getTransform()->getPosition();

			MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent)->getTransform()->setPosition(Vector3(pos.X, pos.Y - 200, pos.Z));


			//Estos cerca
			std::string ent2 = "mini_" + std::to_string(k);

			Vector3 pos2 = MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent2)->getTransform()->getPosition();

			MotorCasaPaco::getInstance()->getSceneManager()->getInstance()->getCurrentScene()->getEntity(ent2)->getTransform()->setPosition(Vector3(pos2.X, pos2.Y + 200, pos2.Z));

			if (k == 8)
				minis1far = true;
		}
	}
}

void LevelSelectionComponent::init(json& j)
{
	if (!j["topButtons"].is_null() && j["topButtons"].is_array() && !j["botButtons"].is_null() && j["botButtons"].is_array() && !j["leftArrow"].is_null() && !j["rightArrow"].is_null() && !j["delay"].is_null() && !j["extraButton"].is_null())
	{
		float x;
		float y;

		std::vector<std::string> vec = j["topButtons"];
		
		int count = 0;
		
		for (std::string name : vec) {

			x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			
			positionsX.push_back(x);

			if (count == 0)
			{
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsY.push_back(y);
			}
			assignFunctions(count, name);

			texts.push_back(MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getWindowElement());

			count++;
		}

		std::vector<std::string> vec2 = j["botButtons"];

		for (std::string name : vec2) {

			if (count == 4)
			{
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsY.push_back(y);
			}

			assignFunctions(count, name);

			texts.push_back(MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getWindowElement());

			count++;
		}

		std::vector<std::string> vec3 = j["records"];

		for (std::string name : vec3) {

			records.push_back(GUI_Manager::getInstance()->getRoot()->getChild(name).getWindowElement());
		}

		xLeftArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["leftArrow"]).getCenterPointXAbsolute();
		yLeftArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["leftArrow"]).getCenterPointYAbsolute();

		auto helperFunction = std::bind(&LevelSelectionComponent::functionLeftArrow, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["leftArrow"]), helperFunction);

		xRightArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["rightArrow"]).getCenterPointXAbsolute();
		yRightArrow = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["rightArrow"]).getCenterPointYAbsolute();

		auto helperFunction1 = std::bind(&LevelSelectionComponent::functionRightArrow, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["rightArrow"]), helperFunction1);

		//ExtraButton
		xExtraButton = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["extraButton"]).getCenterPointXAbsolute();
		yExtraButton = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(j["extraButton"]).getCenterPointYAbsolute();


		delay = j["delay"];
		currentTime = MotorCasaPaco::getInstance()->getTime();
		
		currentShow = 0;
		levels = { "nivel 1", "nivel 2", "nivel 3", "nivel 4", "nivel 5", "nivel 7", "nivel 8", "nivel 9" };

		updateTexts(currentShow);
		//std::cout << tam << "\n";
		
		posX = 0;
		posY = 0;

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[posX], positionsY[posY]);
	}
}
