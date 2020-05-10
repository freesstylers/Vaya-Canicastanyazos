#pragma once
#include "Entity/Component.h"

class GoalComponent : public Component
{
public:
	GoalComponent(json& args);
	~GoalComponent();
	void init(json& args) override;
	virtual void OnCollision(Entity* ent) override;

private:
	std::string scene;
};