#pragma once
#include "Entity/Component.h"

class DeathZoneComponent : public Component
{
public:
	DeathZoneComponent(json& args);
    void init(json& args) override;
	void update() override;
	~DeathZoneComponent();

private:
	Entity* marble;
};