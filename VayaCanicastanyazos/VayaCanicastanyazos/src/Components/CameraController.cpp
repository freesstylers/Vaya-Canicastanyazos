#include "CameraController.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Graphics/Camera.h"

#include <cmath>

CameraController::CameraController(json& args) : Component(args)
{

}

CameraController::~CameraController()
{

}

void CameraController::init(json& args)
{
	orbitSpeed = 0.2f;

	orbitLerpSpeed = 10.0f;
	vertLerpSpeed = 8.0f;
	horizLerpSpeed = 8.0f;

	zoomSpeed = 0.1f;
	zoomInLimit = 50.0f;
	zoomOutLimit = 250.0f;

	horizontalLimit = 10.0f;
	verticalLimit = 15.0f;

	marbleName = "ball";

	if (!args["orbitSpeed"].is_null())
		orbitSpeed = args["orbitSpeed"];

	if (!args["zoomSpeed"].is_null())
		zoomSpeed = args["zoomSpeed"];
	if (!args["zoomInLimit"].is_null())
		zoomInLimit = args["zoomInLimit"];
	if (!args["zoomOutLimit"].is_null())
		zoomOutLimit = args["zoomOutLimit"];

	if (!args["horizontalDegreeLimit"].is_null())
		horizontalLimit = args["horizontalDegreeLimit"];
	if (!args["verticalDegreeLimit"].is_null())
		verticalLimit = args["verticalDegreeLimit"];

	if (!args["orbitLerpSpeed"].is_null())
		orbitLerpSpeed = args["orbitLerpSpeed"];
	if (!args["vertLerpSpeed"].is_null())
		vertLerpSpeed = args["vertLerpSpeed"];
	if (!args["horizLerpSpeed"].is_null())
		horizLerpSpeed = args["horizLerpSpeed"];

	if (!args["marble"].is_null())
	{
		std::string aux = args["marble"];
		marbleName = aux;
	}

	marble = SceneManager::getInstance()->getCurrentScene()->getEntity(marbleName);

	//getEntity()->getComponent<Transform>("Transform")->setInheritedRotation(false);
}

void CameraController::redefine(json& args)
{
	if (args["rotationSpeed"].is_null())
		args["rotationSpeed"] = orbitSpeed;

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

	if (args["horizontalDegreeLimit"].is_null())
		args["horizontalDegreeLimit"] = horizontalLimit;
	if (args["verticalDegreeLimit"].is_null())
		args["verticalDegreeLimit"] = verticalLimit;

	if (args["orbitLerpSpeed"].is_null())
		args["orbitLerpSpeed"] = orbitLerpSpeed;
	if (args["vertLerpSpeed"].is_null())
		args["vertLerpSpeed"] = vertLerpSpeed;
	if (args["horizLerpSpeed"].is_null())
		args["horizLerpSpeed"] = horizLerpSpeed;

	init(args);
}

void CameraController::start()
{
	pivot = getEntity()->getParent();
	getEntity()->getComponent<Camera>("Camera")->lookAt(marble->getTransform()->getWorldPosition());


	getEntity()->getTransform()->setRotation(Vector3(0, 0, 0));
}

void CameraController::preupdate()
{
	preBallPos = marble->getTransform()->getWorldPosition();
}

void CameraController::update()
{

	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	Transform* pivotTransform = pivot->getComponent<Transform>("Transform");
	Transform* marbleTrans = marble->getComponent<Transform>("Transform");

	float deltatime = MotorCasaPaco::getInstance()->DeltaTime() * 1000;

//translate camera to follow ball
	Vector3 ballMovement = marbleTrans->getWorldPosition() - preBallPos;
	pivotTransform->translate(ballMovement, TransformSpace::WORLD);

//orbit around ball
	float rightx = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTX, false);

	prevOrbit = Lerp(prevOrbit, rightx, (orbitLerpSpeed) * deltatime / 1000.0f);
	rightx = prevOrbit;

	pivotTransform->rotate(Vector3(0, orbitSpeed * -rightx * deltatime, 0), TransformSpace::WORLD);

	transform->lookAt(marbleTrans->getWorldPosition());

//zoom
	bool out = InputManager::getInstance()->GameControllerIsButtonDown(CONTROLLER_BUTTON_LEFTSHOULDER);
	bool in = InputManager::getInstance()->GameControllerIsButtonDown(CONTROLLER_BUTTON_RIGHTSHOULDER);

	Vector3 dir = Vector3(marbleTrans->getWorldPosition() - transform->getWorldPosition());
	Vector3 normDir = Vector3::Normalized(dir);

	if (out && Vector3::Distance(dir, normDir) <= zoomOutLimit)
		transform->translate(-1 * deltatime * normDir * zoomSpeed, TransformSpace::WORLD);
	else if (in && Vector3::Distance(dir, normDir) >= zoomInLimit)
		transform->translate(deltatime * normDir * zoomSpeed, TransformSpace::WORLD);

//faking world rotation

	float x = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	float y = -InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);


	//for convenience, we lerp the input instead of the vectors
	prevX = Lerp(prevX, x, (horizLerpSpeed) * deltatime / 1000.0f);
	x = prevX;

	prevY = Lerp(prevY, y, (vertLerpSpeed) * deltatime / 1000.0f);
	y = prevY;

//y (vertical) faked rotation


	float vert = (y * verticalLimit);

	Vector3 vertRot = Vector3::Cross(normDir, Vector3::Backward()) * vert;

	Vector3 actualPivotRot = Quaternion::ToEuler(pivotTransform->getRotation());

	Vector3 newPivotRot = Vector3(vertRot.X, actualPivotRot.Y, actualPivotRot.Z);

	pivotTransform->setRotation(newPivotRot);

	transform->lookAt(marbleTrans->getWorldPosition());


//x (horizontal) faked rotation

	float horizontal = (x * horizontalLimit);

	Vector3 actualCamRot = Quaternion::ToEuler(transform->getRotation());
	Vector3 newCamRot = Vector3::Forward() * horizontal;

	transform->setRotation(newCamRot);
}