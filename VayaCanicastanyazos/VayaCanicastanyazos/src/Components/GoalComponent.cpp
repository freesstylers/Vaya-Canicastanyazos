#include "GoalComponent.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Entity/Transform.h"
#include <iostream>

GoalComponent::GoalComponent(json& args) : Component(args)
{

}

GoalComponent::~GoalComponent() {
	Component::~Component();
}

std::string tostring(const std::string& name) {
	return name;
}

void GoalComponent::init(json& args) {
	if (!args["marble"].is_null())
		marble = SceneManager::getInstance()->getCurrentScene()->getEntity(args["marble"]);
	if (!args["scene"].is_null())
		scene = tostring(args["scene"]);
}

void GoalComponent::update() {
	if (marble->getTransform()->getPosition().Y < Component::getEntity()->getTransform()->getPosition().Y)
		MotorCasaPaco::getInstance()->changeScene(scene);
}

