#pragma once
#include "Entity/Component.h"

class FakeRotation : public Component
{
public:
	FakeRotation(json& args);
	void start() override;
	void update() override;
	~FakeRotation();

	void init(json& args) override;
private:
	float speed = 50;
	Vector3 rotation = Vector3(0, 0, 0);
	Entity* camera;

	bool monkey = false;
	std::string camName = "camera";

	float maxAngle = 45.0f;
};

