#include "GoalComponent.h"
#include "Scene/SceneManager.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

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
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0); //Bastante cursed porque como que se stackea
	MotorCasaPaco::getInstance()->changeScene(nextLevel);
	return true;
}

bool GoalComponent::functionBasicLevelSelection(const CEGUI::EventArgs& e)
{
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0); //Bastante cursed porque como que se stackea
	MotorCasaPaco::getInstance()->changeScene(levelSelection);
	return true;
}

void GoalComponent::init(json& args) {
	if (!args["nextLevel"].is_null() && !args["levelSelection"].is_null())
	{
		nextLevel = tostring(args["nextLevel"]);
		levelSelection = tostring(args["levelSelection"]);
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
		}

		//Update Text
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Time"), "Tiempo: " + std::to_string(GameManager::getInstance()->getLevelTime()));
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Record"), "Record: " + std::to_string(GameManager::getInstance()->getTimeFromLevel(1))); //El 1 está de stub, habría que meter un campo level en el componente?

		
		//Falta el texto, y actualizar las estrellas
	}
}

void GoalComponent::OnCollision(Entity* ent) {
	if (ent->getTag() == "marble") {
		EventManager::getInstance()->EmitEvent("finNivel");
		
		setLayout();
		GUI_Manager::getInstance()->setLayoutVisible(0, false);

		GUI_Manager::getInstance()->setLayoutVisible(GUI_Manager::getInstance()->getLayouts().size() - 1, true);
	}
}

