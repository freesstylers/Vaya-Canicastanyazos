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
	MotorCasaPaco::getInstance()->changeScene(nextLevel);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0); //Bastante cursed porque como que se stackea
	return true;
}

bool GoalComponent::functionBasicLevelSelection(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(levelSelection);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
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

		//Falta el texto, y actualizar las estrellas
	}
}

void GoalComponent::OnCollision(Entity* ent) {
	if (ent->getTag() == "marble") {
		EventManager::getInstance()->EmitEvent("finNivel");
		
		setLayout();
		GUI_Manager::getInstance()->setLayoutVisible(0, false);

		//Update Text
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Time"), std::to_string(GameManager::getInstance()->getLevelTime()));
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("levelCompleted/Record"), std::to_string(GameManager::getInstance()->getTimeFromLevel(1))); //El 1 está de stub, habría que meter un campo level en el componente?

		GUI_Manager::getInstance()->setLayoutVisible(GUI_Manager::getInstance()->getLayouts().size() - 1, true);
	}
}

