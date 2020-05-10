#pragma once
#include "Entity/Component.h"

class DeathZoneComponent : public Component
{
public:
	DeathZoneComponent(json& args);
	~DeathZoneComponent();

	virtual void OnCollision(Entity* ent) override;
};