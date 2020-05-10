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

	//Pause Menu
	bool functionPauseReturn(const CEGUI::EventArgs& e);
	bool functionPauseReset(const CEGUI::EventArgs& e);
	bool functionPauseSettings(const CEGUI::EventArgs& e);
	bool functionPauseMainMenu(const CEGUI::EventArgs& e);
	bool functionPauseExit(const CEGUI::EventArgs& e);
	
	//Basic Options
	bool functionBasicGraphicOptions(const CEGUI::EventArgs& e);
	bool functionBasicBack(const CEGUI::EventArgs& e);


	//Graphic Options
	bool functionGraphicAdvancedOptions(const CEGUI::EventArgs& e);
	bool functionGraphicApply(const CEGUI::EventArgs& e);
	bool functionGraphicRevert(const CEGUI::EventArgs& e);
	bool functionGraphicBack(const CEGUI::EventArgs& e);

	//Advanced Options
	bool functionAdvancedBack(const CEGUI::EventArgs& e);


	void update() override;
	void pausedUpdate() override;

private:
	//Delays
	float delay;
	float delayPause;
	float currentTime;

	//Vainas de menus
	int layoutLayer;
	float currentXTopButtons;
	float currentYTopButtons;
	float currentPosDownButtons;
	//float currentYButtons;

	//Pause
	std::vector<float> positionsYPause;
	int currenPos;
	float xPause;
	int tamPause;

	//Basic
	std::vector<float> positionsYBasic;
	std::vector<float> positionsXBotButtonsBasic;
	std::vector<float> positionsXTopButtonsBasic;
	float yBasicExtra;
	float xBasicExtra;	
	float yBasicBack;
	float xBasicBack;
	int tamBasicTop;
	int basicTopDown = 2;

	//Graphic
	std::vector<float> positionsYGraphic;
	std::vector<float> positionsXBotButtonsGraphic;
	std::vector<float> positionsXTopButtonsGraphic;
	float yGraphicBot;
	float xExtraGraphic;
	float yExtraGraphic;
	int tamGraphicDown;
	int tamGraphicTop;
	int graphicTopDown = 2;

	//Advanced
	std::vector<float> positionsYAdvanced;
	std::vector<float> positionsXBotButtonsAdvanced;
	std::vector<float> positionsXTopButtonsAdvanced;
	float yAdvancedBot;
	int tamAdvancedTop;
	int tamAdvancedDown;
	int advancedTopDown = 1;

	//Datos de escenas
	std::string mainMenu;
	std::string level;
};



#endif

