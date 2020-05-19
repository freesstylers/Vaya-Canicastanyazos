#include "DeathZoneComponent.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Entity/Transform.h"
#include "GameManager.h"
#include <iostream>

DeathZoneComponent::DeathZoneComponent(json& args) : Component(args)
{

}

DeathZoneComponent::~DeathZoneComponent() {

}

void DeathZoneComponent::init(json& args) {
	if (!args["entity"].is_null())
	{
		marble = SceneManager::getInstance()->getCurrentScene()->getEntity(args["entity"]);
	}
}

void DeathZoneComponent::update() {
	if (marble->getTransform()->getPosition().Y < getEntity()->getTransform()->getPosition().Y) {
		MotorCasaPaco::getInstance()->changeScene(MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getName());
	}
}


