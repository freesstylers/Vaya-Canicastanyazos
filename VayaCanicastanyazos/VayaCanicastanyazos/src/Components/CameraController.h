#pragma once
#include "Entity/Component.h"

class CameraController : public Component
{
public:
	CameraController(json& args);
	virtual void update();
	void init(json& args) override;
	void redefine(json& args) override;
	~CameraController();

private:
	float rotationSpeed;
	Entity* marble;
	Vector3 cameraOffset;
};

