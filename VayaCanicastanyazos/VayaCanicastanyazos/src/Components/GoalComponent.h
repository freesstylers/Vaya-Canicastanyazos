#pragma once
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class GoalComponent : public Component
{
public:
	GoalComponent(json& args);
	~GoalComponent();
	void init(json& args) override;
	virtual void OnCollision(Entity* ent) override;
	bool functionBasicNextLevel(const CEGUI::EventArgs& e);
	bool functionBasicLevelSelection(const CEGUI::EventArgs& e);

private:
	void setLayout();
	std::string nextLevel;
	std::string levelSelection;
};