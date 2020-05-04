#include "CameraController.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Graphics/Camera.h"

CameraController::CameraController(json& args) : Component(args)
{

}

CameraController::~CameraController()
{

}

void CameraController::init(json& args)
{
	rotationSpeed = 2.0f;
	zoomSpeed = 1.0f;
	zoomInLimit = 50.0f;
	zoomOutLimit = 250.0f;
	marbleName = "ball";

	if (!args["rotationSpeed"].is_null())
		rotationSpeed = args["rotationSpeed"];
	if (!args["zoomSpeed"].is_null())
		zoomSpeed = args["zoomSpeed"];
	if (!args["zoomInLimit"].is_null())
		zoomInLimit = args["zoomInLimit"];
	if (!args["zoomOutLimit"].is_null())
		zoomOutLimit = args["zoomOutLimit"];
	if (!args["marble"].is_null())
		marbleName = args["marble"];

	marble = SceneManager::getInstance()->getCurrentScene()->getEntity(marbleName);
	getEntity()->getComponent<Transform>("Transform")->setInheritedRotation(false);

	cameraOffset = getEntity()->getComponent<Transform>("Transform")->getPosition();
}

void CameraController::redefine(json& args)
{
	if (args["rotationSpeed"].is_null())
		args["rotationSpeed"] = rotationSpeed;
	if (args["zoomSpeed"].is_null())
		args["zoomSpeed"] = zoomSpeed;
	if (args["zoomInLimit"].is_null())
		args["zoomInLimit"] = zoomInLimit;
	if (args["zoomOutLimit"].is_null())
		args["zoomOutLimit"] = zoomOutLimit;
	if (args["zoomOutLimit"].is_null())
		args["zoomOutLimit"] = zoomOutLimit;
	if (args["marble"].is_null())
		args["marble"] = marbleName;

	init(args);
}

void CameraController::preupdate()
{
	preBallPos = marble->getTransform()->getWorldPosition();
}

void CameraController::update()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	Transform* marbleTrans = marble->getComponent<Transform>("Transform");

	//translate camera to follow ball
	Vector3 ballMovement = marbleTrans->getWorldPosition() - preBallPos;
	transform->translate(ballMovement);


	//orbit around ball
	float rightx = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTX, false);
	transform->rotateAroundPivot(Vector3(0, rotationSpeed * -rightx * MotorCasaPaco::getInstance()->DeltaTime() / 10, 0), marble);

	getEntity()->getComponent<Camera>("Camera")->lookAt(marbleTrans->getWorldPosition());


	//zoom
	bool out = InputManager::getInstance()->GameControllerIsButtonDown(CONTROLLER_BUTTON_LEFTSHOULDER);
	bool in = InputManager::getInstance()->GameControllerIsButtonDown(CONTROLLER_BUTTON_RIGHTSHOULDER);

	Vector3 dir = Vector3(marbleTrans->getWorldPosition() - transform->getWorldPosition());
	Vector3 normDir = Vector3::Normalized(dir);

	if (Vector3::Distance(dir, normDir) <= zoomOutLimit && out)
		transform->translate(-1 * MotorCasaPaco::getInstance()->DeltaTime() * normDir * zoomSpeed);
	else if (Vector3::Distance(dir, normDir) >= zoomInLimit && in)
		transform->translate(MotorCasaPaco::getInstance()->DeltaTime() * normDir * zoomSpeed);
}