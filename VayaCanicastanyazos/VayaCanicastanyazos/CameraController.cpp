#include "CameraController.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"

CameraController::CameraController(json& args) : Component(args)
{

}

CameraController::~CameraController()
{

}
void CameraController::init(json& args)
{
	rotationSpeed = 2.0f;
	if (!args["rotationSpeed"].is_null())
		rotationSpeed = args["rotationSpeed"];
	if(!args["marble"].is_null())
		marble = SceneManager::getInstance()->getCurrentScene()->getEntity(args["marble"]);
	getEntity()->getComponent<Transform>("Transform")->setInheritedRotation(false);
}

void CameraController::redefine(json& args)
{
	if (args["rotationSpeed"].is_null())
		args["rotationSpeed"] = rotationSpeed;
	init(args);
}

void CameraController::update()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	Transform* marbleTrans = marble->getComponent<Transform>("Transform");

	float rightx = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTX, false);
	float righty = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTY, false);

	transform->rotate(Vector3(0, rotationSpeed * -rightx * MotorCasaPaco::getInstance()->DeltaTime(),0));
	//transform->translate(Vector3(0, righty * transform->getPosition().Angle(transform->getPosition(), marbleTrans->getPosition()), rotationSpeed * righty * MotorCasaPaco::getInstance()->DeltaTime()));
}