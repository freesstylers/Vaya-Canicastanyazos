#include "GoalComponent.h"
#include "Scene/SceneManager.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"

GoalComponent::GoalComponent(json& args) : Component(args)
{

}

GoalComponent::~GoalComponent() {

}

std::string tostring(const std::string& name) {
	return name;
}

bool GoalComponent::functionBasicNextLevel(const CEGUI::EventArgs& e)
{
	GameManager::getInstance()->pause();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 2, false);
	MotorCasaPaco::getInstance()->changeScene(nextLevel);
	GUI_Manager::getInstance()->hideMouseCursor();
	return true;
}

bool GoalComponent::functionBasicLevelSelection(const CEGUI::EventArgs& e)
{
	GameManager::getInstance()->pause();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 2, false);
	MotorCasaPaco::getInstance()->changeScene(levelSelection);
	AudioManager::getInstance()->pauseChannel(1);
	AudioManager::getInstance()->playMusic("assets/sound/Menu_Music.mp3", 1, true);
	return true;
}

bool GoalComponent::functionBasicRepeatLevel(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(level);
	GameManager::getInstance()->pause();
	EventManager::getInstance()->EmitEvent("inicioNivel");
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 2, false);
	GUI_Manager::getInstance()->hideMouseCursor();
	return true;
}

void GoalComponent::pausedUpdate()
{
	if (completed)
	{
		if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
		{
			//Mando y tal

			if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
			{
				if (levelMenuUp)
				{
					if (menuPos == 0)
						menuPos = 1;
					else
						menuPos = 0;

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yTop);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}

			}
			else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
			{
				if (levelMenuUp)
				{
					if (menuPos == 0)
						menuPos = 1;
					else
						menuPos = 0;

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yTop);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}

			else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
			{
				if (levelMenuUp)
				{
					levelMenuUp = false;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBot, yBot);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
				else
				{
					levelMenuUp = true;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yTop);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}

			else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
			{
				if (levelMenuUp)
				{
					levelMenuUp = false;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBot, yBot);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
				else
				{
					levelMenuUp = true;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yTop);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}
		}

		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
	}
}

void GoalComponent::init(json& args) {
	if (!args["nextLevel"].is_null() && !args["level"].is_null() && !args["levelSelection"].is_null() && !args["delay"].is_null())
	{
		nextLevel = tostring(args["nextLevel"]);
		levelSelection = tostring(args["levelSelection"]);
		level = tostring(args["level"]);
		delay = args["delay"];

		currentTime = MotorCasaPaco::getInstance()->getTime();
	}
}

void GoalComponent::setLayout()
{
	if (GUI_Manager::getInstance()->getLayouts().size() == 6) //Para comprobar que se han cargado todos los layouts, ya que este componente se carga antes que los layouts
	{
		//Funciones de los botones
		auto Function1 = std::bind(&GoalComponent::functionBasicLevelSelection, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("levelCompleted/Selection"), Function1);

		auto Function2 = std::bind(&GoalComponent::functionBasicNextLevel, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("levelCompleted/NextLevel"), Function2);

		auto Function3 = std::bind(&GoalComponent::functionBasicRepeatLevel, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("levelCompleted/Repeat"), Function3);

		int stars = GameManager::getInstance()->getStars();

		std::string id = "levelCompleted/Star";
		int i = 1;

		while (i <= stars)
		{
			GUI_Manager::getInstance()->changeImage(id + std::to_string(i), "VayaCanicastanhazos/Star_Yes");
			i++;
		}

		//Update Text
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Time"), "Tiempo: " + std::to_string(GameManager::getInstance()->getLevelTime()));
		

		std::string s;
		int r = rand() % 3;

		switch (r)
		{
		case 0:
			s = "VayaCanicastanhazos/Bocadillo_Izq_1";
			break;
		case 1:
			s = "VayaCanicastanhazos/Bocadillo_Izq_2";
			break;
		case 2:
			s = "VayaCanicastanhazos/Bocadillo_Izq_3";
			break;
		case 3:
			s = "VayaCanicastanhazos/Bocadillo_Izq_4";
			break;
		default:
			break;
		}

		GUI_Manager::getInstance()->changeImage("levelCompleted/TextoYayo1", s);

		r = rand() % 3;

		switch (r)
		{
		case 0:
			s = "VayaCanicastanhazos/Bocadillo_Dcha_1";
			break;
		case 1:
			s = "VayaCanicastanhazos/Bocadillo_Dcha_2";
			break;
		case 2:
			s = "VayaCanicastanhazos/Bocadillo_Dcha_3";
			break;
		case 3:
			s = "VayaCanicastanhazos/Bocadillo_Dcha_4";
			break;
		default:
			break;
		}

		GUI_Manager::getInstance()->changeImage("levelCompleted/TextoYayo2", s);


		xPos[0] = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/Selection").getCenterPointXAbsolute();
		yTop = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/Selection").getCenterPointYAbsolute();
		xPos[1] = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/NextLevel").getCenterPointXAbsolute();

		yBot = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/Repeat").getCenterPointYAbsolute();
		xBot = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/Repeat").getCenterPointXAbsolute();
		//Falta el texto, y actualizar las estrellas
	}
}

void GoalComponent::OnCollision(Entity* ent) {
	
	if (!set)
	{
		setLayout();
		set = true;
	}

	if (!completed)
	{
		if (ent->getTag() == "marble") {

			Event evt = Event("nivelCompletado");
			EventManager::getInstance()->EmitEvent(evt);

			Event evt2 = Event("finNivel");
			EventManager::getInstance()->EmitEvent(evt2);

			std::size_t position = nextLevel.find(" ");
			std::string levelNumber = nextLevel.substr(position);
			int level = std::stoi(levelNumber);

			GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Record"), "Record: " + std::to_string(GameManager::getInstance()->getTimeFromLevel(level - 1)));


			GUI_Manager::getInstance()->setLayoutVisible(0, false);

			GUI_Manager::getInstance()->setLayoutVisible(GUI_Manager::getInstance()->getLayouts().size() - 1, true);
			GUI_Manager::getInstance()->showMouseCursor();

			GameManager::getInstance()->pause();
			AudioManager::getInstance()->playMusic("assets/sound/victory.mp3", 3, false);

			completed = true;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yTop);
		}
	}
}

