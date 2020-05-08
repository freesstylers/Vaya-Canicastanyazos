#pragma once
#include "Entity/Component.h"

class StarCollision : public Component
{
public:
	StarCollision(json& args);
	~StarCollision();

	virtual void OnCollision(Entity* ent) override;
	virtual void update() override;
	void init(json& j) override;

private:
	float rotation_ = 0.1;
};