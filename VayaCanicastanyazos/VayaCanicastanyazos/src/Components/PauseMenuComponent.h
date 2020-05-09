#pragma once
#ifndef PAUSEMENUCOMPONENT_H
#define PAUSEMENUCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class PauseMenuComponent : public Component
{

public:
	PauseMenuComponent(json& args);
	~PauseMenuComponent();
	void init(json& j) override;
	bool ReceiveEvent(Event& event);
	bool functionReturn(const CEGUI::EventArgs& e);
	bool functionReset(const CEGUI::EventArgs& e);
	bool functionSettings(const CEGUI::EventArgs& e);
	bool functionMainMenu(const CEGUI::EventArgs& e);
	bool functionExit(const CEGUI::EventArgs& e);
	void update() override;
	void pausedUpdate() override;

private:
	float delay;
	float delayPause;
	float currentTime;
	int currenPos;
	std::vector<float> positionsY;
	float x;
	int tam;
	std::string mainMenu;
	std::string level;
};



#endif

