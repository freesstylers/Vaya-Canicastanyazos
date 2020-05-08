#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"
#include "Audio/AudioManager.h"
#include "MotorCasaPaco.h"
#include "FakeRotation.h"
#include "Scene/SceneManager.h"
#include "Graphics/Camera.h"
#include <math.h>

FakeRotation::FakeRotation(json& args) : Component(args)
{

}

FakeRotation::~FakeRotation()
{

}


void FakeRotation::init(json& args)
{
	speed = 10.0f;

	if (!args["camName"].is_null())
	{
		std::string aux = args["camName"];
		camName = aux;
	}
	if (!args["speed"].is_null())
		speed = args["speed"];
}

void FakeRotation::start()
{
	camera = SceneManager::getInstance()->getCurrentScene()->getEntity(camName);
}

void FakeRotation::update()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	Transform* camPivotTransform = camera->getParent()->getComponent<Transform>("Transform");
	Transform* camTransform = camera->getComponent<Transform>("Transform");

	float deltatime = MotorCasaPaco::getInstance()->DeltaTime() * 1000;

	float x = -InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	float y = -InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);

	Vector3 camLook = transform->getWorldPosition() - camTransform->getWorldPosition();
	camLook.Y = 0;
	Vector3 camOrthoLook = Quaternion::FromAngleAxis(90, Vector3::Up()) * camLook;
	camOrthoLook = Vector3::Normalized(camOrthoLook);
	camLook = Vector3::Normalized(camLook);

	getEntity()->getComponent<RigidBody>("RigidBody")->applyForce(ForceType::FORCE, camLook * speed * y * deltatime);
	getEntity()->getComponent<RigidBody>("RigidBody")->applyForce(ForceType::FORCE, camOrthoLook * speed * x * deltatime);
}