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

void DeathZoneComponent::OnCollision(Entity* ent) {
	if (ent->getTag() == "marble") {
		MotorCasaPaco::getInstance()->changeScene(MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getName());
		GameManager::getInstance()->resetStars();
	}
}


