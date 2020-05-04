#pragma once
#include "Entity/Component.h"

class RotateWorld : public Component
{
public:
	RotateWorld(json& args);
	void start() override;
	void update() override;
	~RotateWorld();

	void init(json& args) override;
private:
	float speed = 20;
	Vector3 rotation = Vector3(0, 0, 0);
	Entity* camera;

	bool monkey = false;
	std::string camName = "camera";
};

