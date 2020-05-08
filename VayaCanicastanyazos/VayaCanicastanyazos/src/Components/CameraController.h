#pragma once
#include "Entity/Component.h"

class CameraController : public Component
{
public:
	CameraController(json& args);
	virtual void update();
	void init(json& args) override;
	void redefine(json& args) override;
	void start() override;
	void preupdate() override;
	~CameraController();

private:
	float orbitSpeed;
	std::string marbleName;
	Entity* marble;
	Entity* pivot = nullptr;

	Vector3 preBallPos = Vector3(0, 0, 0);

	float zoomInLimit;
	float zoomOutLimit;
	float zoomSpeed;

	float horizontalLimit;
	float verticalLimit;

	float prevX = 0.0f;
	float prevY = 0.0f;
	float prevOrbit = 0.0f;

	float horizLerpSpeed;
	float vertLerpSpeed;
	float orbitLerpSpeed;
};

