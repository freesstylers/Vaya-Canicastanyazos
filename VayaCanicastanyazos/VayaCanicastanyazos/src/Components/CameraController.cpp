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

	horizontalLimit = 15.0f;
	verticalLimit = 15.0f;

	marbleName = "ball";

	if (!args["rotationSpeed"].is_null())
		rotationSpeed = args["rotationSpeed"];

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

	if (args["horizontalDegreeLimit"].is_null())
		args["horizontalDegreeLimit"] = horizontalLimit;
	if (args["verticalDegreeLimit"].is_null())
		args["verticalDegreeLimit"] = verticalLimit;

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

	if (out && Vector3::Distance(dir, normDir) <= zoomOutLimit)
		transform->translate(-1 * MotorCasaPaco::getInstance()->DeltaTime() * normDir * zoomSpeed);
	else if (in && Vector3::Distance(dir, normDir) >= zoomInLimit)
		transform->translate(MotorCasaPaco::getInstance()->DeltaTime() * normDir * zoomSpeed);




	//faking world rotation

	float x = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	float y = -InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);

	Vector3 actualRot = Quaternion::ToEuler(transform->getRotation());

	//y (vertical) faked rotation

	float vert = (y * verticalLimit) - prevVertical;

	Vector3 vertRot = Vector3::Cross(normDir, Vector3::Up()) * vert;

	transform->rotateAroundPivot(vertRot, marble);

	prevVertical = y * verticalLimit;

	getEntity()->getComponent<Camera>("Camera")->lookAt(marbleTrans->getWorldPosition());


	//x (horizontal) faked rotation

	//float horizontal = (x * horizontalLimit) - prevHorizontal;

	//Vector3 horizontalRot = Vector3::Backward() * horizontal;

	//transform->rotate(horizontalRot, TransformSpace::WORLD);

	//prevHorizontal = x * horizontalLimit;

	//getEntity()->getComponent<Camera>("Camera")->lookAt(marbleTrans->getWorldPosition());


	//add lerping to orbit and fake world movement?



	//getEntity()->getComponent<Camera>("Camera")->lookAt(marbleTrans->getWorldPosition());

}