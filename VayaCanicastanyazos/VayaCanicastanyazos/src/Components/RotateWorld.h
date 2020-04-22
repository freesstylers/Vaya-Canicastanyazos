#pragma once
#include "Entity/Component.h"

class RotateWorld : public Component
{
public:
	RotateWorld(json& args);
	virtual void start();
	virtual void update();
	~RotateWorld();
private:
	float speed = 20;
	Vector3 rotation;
};

