#pragma once
#include "Entity/Component.h"

class GoalComponent : public Component
{
public:
	GoalComponent(json& args);
	void init(json& args) override;
	void update() override;
	~GoalComponent();

private:
	Entity* marble;
	std::string scene;
};