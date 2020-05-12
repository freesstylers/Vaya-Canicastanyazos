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
	bool functionBasicApply(const CEGUI::EventArgs& e);
	bool functionBasicRevert(const CEGUI::EventArgs& e);


	//Graphic Options
	bool functionGraphicAdvancedOptions(const CEGUI::EventArgs& e);
	bool functionGraphicApply(const CEGUI::EventArgs& e);
	bool functionGraphicRevert(const CEGUI::EventArgs& e);
	bool functionGraphicBack(const CEGUI::EventArgs& e);
	bool functionGraphicFullScreen(const CEGUI::EventArgs& e);
	bool functionGraphicVSync(const CEGUI::EventArgs& e);
	bool functionGraphicFormatMore(const CEGUI::EventArgs& e);
	bool functionGraphicFormatLess(const CEGUI::EventArgs& e);
	bool functionGraphicResolutionMore(const CEGUI::EventArgs& e);
	bool functionGraphicResolutionLess(const CEGUI::EventArgs& e);

	//Advanced Options
	bool functionAdvancedApply(const CEGUI::EventArgs& e);
	bool functionAdvancedRevert(const CEGUI::EventArgs& e);
	bool functionAdvancedBack(const CEGUI::EventArgs& e);
	bool functionAdvancedShadowsLess(const CEGUI::EventArgs& e);
	bool functionAdvancedShadowsMore(const CEGUI::EventArgs& e);
	bool functionAdvancedGamma(const CEGUI::EventArgs& e);
	bool functionAdvancedFSAALess(const CEGUI::EventArgs& e);
	bool functionAdvancedFSAAMore(const CEGUI::EventArgs& e);


	void update() override;
	void pausedUpdate() override;

	bool optionsAssert(json& j);

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
	float yBasicBot;
	float xBasicBot;
	int tamBasicTop;
	int tamBasicBot;
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
	std::vector<CEGUI::Window*> graphicTexts; //fullscreenText, formatText, resolutionText, vSyncText
	std::string currentFormat;
	std::string currentRes;
	std::vector<std::vector<std::string>> resolutions;
	int getCurrentPosForRes(std::string currentFormat_, std::string currentRes_);
	int ForResPosition;

	//Advanced
	std::vector<float> positionsYAdvanced;
	std::vector<float> positionsXBotButtonsAdvanced;
	std::vector<float> positionsXTopButtonsAdvanced;
	float yAdvancedBot;
	int tamAdvancedTop;
	int tamAdvancedDown;
	int advancedTopDown = 1;
	std::string shadowValues[4] = { "No" , "Bajo", "Medio", "Alto" };
	int getShadowsPosition(std::string shadow);
	int shadowsPos;
	std::vector<CEGUI::Window*> advancedTexts; //fullscreenText, formatText, resolutionText, vSyncText
	std::string fsaaValues[4] = { "0" , "2", "4", "8" };
	int getFSAAPosition(std::string fsaa);
	int fsaaPos;

	//Datos de escenas
	std::string mainMenu;
	std::string level;
};



#endif

