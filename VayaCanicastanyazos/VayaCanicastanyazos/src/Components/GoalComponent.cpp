#include "GoalComponent.h"
#include "Scene/SceneManager.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"

GoalComponent::GoalComponent(json& args) : Component(args)
{

}

GoalComponent::~GoalComponent() {

}

std::string tostring(const std::string& name) {
	return name;
}

void GoalComponent::init(json& args) {
	if (!args["scene"].is_null())
		scene = tostring(args["scene"]);
}

void GoalComponent::OnCollision(Entity* ent) {
	if (ent->getTag() == "marble") {
		EventManager::getInstance()->EmitEvent("finNivel");
		MotorCasaPaco::getInstance()->changeScene(scene);
	}
}

