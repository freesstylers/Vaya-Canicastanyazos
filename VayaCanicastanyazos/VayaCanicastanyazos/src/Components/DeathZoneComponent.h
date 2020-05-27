#pragma once
#include "Entity/Component.h"

class DeathZoneComponent : public Component
{
public:
	DeathZoneComponent(json& args);
	~DeathZoneComponent();

	virtual void init(json& args) override;
	virtual void update() override;

private:
	Entity* marble;
	bool dead = true;
	int time = 0;
};