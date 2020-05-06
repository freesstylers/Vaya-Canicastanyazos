#pragma once
#include "Entity/Component.h"

class CameraController : public Component
{
public:
	CameraController(json& args);
	virtual void update();
	void init(json& args) override;
	void redefine(json& args) override;
	void preupdate() override;
	~CameraController();

private:
	float rotationSpeed;
	std::string marbleName;
	Entity* marble;
	Vector3 cameraOffset;

	Vector3 preBallPos = Vector3(0, 0, 0);

	float zoomInLimit;
	float zoomOutLimit;
	float zoomSpeed;

	float horizontalLimit;
	float verticalLimit;

	float prevHorizontal = 0.0f;
	float prevVertical = 0.0f;
};

