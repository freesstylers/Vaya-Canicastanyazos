#include "DeathZoneComponent.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Entity/Transform.h"
#include <iostream>

DeathZoneComponent::DeathZoneComponent(json& args) : Component(args)
{

}

DeathZoneComponent::~DeathZoneComponent() {
	Component::~Component();
}

void DeathZoneComponent::init(json& args) {
	if (!args["marble"].is_null())
		marble = SceneManager::getInstance()->getCurrentScene()->getEntity(args["marble"]);
}

void DeathZoneComponent::update() {
	if (marble->getTransform()->getPosition().Y < Component::getEntity()->getTransform()->getPosition().Y)
		MotorCasaPaco::getInstance()->changeScene(MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getName());
}

