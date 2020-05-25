#include "DeathZoneComponent.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Entity/Transform.h"
#include "GameManager.h"
#include "Audio/AudioManager.h"
#include <iostream>

DeathZoneComponent::DeathZoneComponent(json& args) : Component(args)
{

}

DeathZoneComponent::~DeathZoneComponent() {

}

void DeathZoneComponent::init(json& args) {
	if (!args["marble"].is_null())
	{
		marble = SceneManager::getInstance()->getCurrentScene()->getEntity(args["marble"]);
	}
}

void DeathZoneComponent::update() {
	if (marble->getTransform()->getPosition().Y < Component::getEntity()->getTransform()->getPosition().Y) {

		if (dead)
		{
			dead = false;
			AudioManager::getInstance()->pauseChannel(2);
			AudioManager::getInstance()->playSound("assets/sound/castanazo.mp3", 5);
		}

			if (!AudioManager::getInstance()->isPlayingChannel(5))
			{
				SceneManager::getInstance()->changeScene(SceneManager::getInstance()->getCurrentScene()->getName());
				AudioManager::getInstance()->pauseChannel(2);
				GameManager::getInstance()->resetStars();
			}
	}
}


