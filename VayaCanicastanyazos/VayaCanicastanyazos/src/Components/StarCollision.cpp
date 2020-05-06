#include "StarCollision.h"
#include "Scene/SceneManager.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"

StarCollision::StarCollision(json& args) : Component (args)
{

}

StarCollision::~StarCollision()
{

}

void StarCollision::init(json& j)
{
	if (!j["rotation"].is_null()) rotation_ = j["rotation"];
}

void StarCollision::OnCollision(Entity* ent)
{
	if (ent->getTag() == "star")
	{
		getEntity()->setEnabled(false);
		GameManager::getInstance()->addStars(1);
		AudioManager::getInstance()->playSound("assets/sound/402Cry.wav", 0);
		std::cout << GameManager::getInstance()->getStars() << std::endl;
	}
}

void StarCollision::update()
{
	e_->getComponent<Transform>("Transform")->rotate(Vector3(0.0f, rotation_, 0.0f));
}
