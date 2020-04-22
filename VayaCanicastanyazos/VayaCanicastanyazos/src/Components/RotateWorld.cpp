#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"
#include "Audio/AudioManager.h"
#include "MotorCasaPaco.h"
#include "RotateWorld.h"

RotateWorld::RotateWorld(json& args) : Component(args)
{

}

RotateWorld::~RotateWorld()
{

}

void RotateWorld::start()
{
	rotation = Vector3(0, 0, 0);
}

void RotateWorld::update()
{
	float deltatime = MotorCasaPaco::getInstance()->DeltaTime();
	deltatime /= 1000.f;
	float x = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	float y = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);

	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	if (!(x == 0 && y == 0))
	{

		x = x * 180;
		y = y * 180;

		Vector3 target(y, 0, -x);

		Vector3 dir = target - rotation;

		if (Vector3::Magnitude(dir) <= 1) dir = Vector3(0, 0, 0);

		float speedmult = Vector3::Magnitude(dir);

		dir = Vector3::Normalized(dir);

		rotation += dir * speed * deltatime * speedmult * 0.5;
		transform->setRotation(rotation);
		transform->rotate(transform->getRotation());
	}

}