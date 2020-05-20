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
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	MotorCasaPaco::getInstance()->changeScene(nextLevel);
	return true;
}

bool GoalComponent::functionBasicLevelSelection(const CEGUI::EventArgs& e)
{
	GameManager::getInstance()->pause();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0, false);
	MotorCasaPaco::getInstance()->changeScene(levelSelection);
	AudioManager::getInstance()->pauseChannel(2);
	AudioManager::getInstance()->playMusic("assets/sound/Menu_Music.mp3", 1, true);
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
				if (menuPos == 0)
					menuPos = 1;
				else
					menuPos = 0;

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yPos);
				currentTime = MotorCasaPaco::getInstance()->getTime();

			}
			else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
			{
				if (menuPos == 0)
					menuPos = 1;
				else
					menuPos = 0;

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yPos);
				currentTime = MotorCasaPaco::getInstance()->getTime();
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
	if (!args["nextLevel"].is_null() && !args["levelSelection"].is_null() && !args["delay"].is_null())
	{
		nextLevel = tostring(args["nextLevel"]);
		levelSelection = tostring(args["levelSelection"]);
		delay = args["delay"];

		currentTime = MotorCasaPaco::getInstance()->getTime();
	}
}

void GoalComponent::setLayout()
{
	if (GUI_Manager::getInstance()->getLayouts().size() == 6) //Para comprobar que se han cargado todos los layouts, ya que este componente se carga antes que los layouts
	{
		//Funciones de los botones
		auto helperFunctionTopGraphic = std::bind(&GoalComponent::functionBasicLevelSelection, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("levelCompleted/Selection"), helperFunctionTopGraphic);

		auto helperFunctionTopGraphic1 = std::bind(&GoalComponent::functionBasicNextLevel, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("levelCompleted/NextLevel"), helperFunctionTopGraphic1);

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
		yPos = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/Selection").getCenterPointYAbsolute();
		xPos[1] = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("levelCompleted/NextLevel").getCenterPointXAbsolute();

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

			GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Record"), "Record: " + std::to_string(GameManager::getInstance()->getTimeFromLevel(level - 1))); //El 1 está de stub, habría que meter un campo level en el componente?


			GUI_Manager::getInstance()->setLayoutVisible(0, false);

			GUI_Manager::getInstance()->setLayoutVisible(GUI_Manager::getInstance()->getLayouts().size() - 1, true);

			GameManager::getInstance()->pause();
			AudioManager::getInstance()->playMusic("assets/sound/victory.mp3", 3, false);

			completed = true;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yPos);
		}
	}
}

