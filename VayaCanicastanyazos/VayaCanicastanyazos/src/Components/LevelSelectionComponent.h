#pragma once
#ifndef LEVELSELECTIONINPUTCOMPONENT_H
#define LEVELSELECTIONINPUTCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class LevelSelectionComponent : public Component
{

public:
	LevelSelectionComponent(json& args);
	~LevelSelectionComponent();
	void init(json& j) override;
	bool functionLoader1(const CEGUI::EventArgs& e);
	bool functionLoader2(const CEGUI::EventArgs& e);
	bool functionLoader3(const CEGUI::EventArgs& e);
	bool functionLoader4(const CEGUI::EventArgs& e);
	bool functionLoader5(const CEGUI::EventArgs& e);
	bool functionLoader6(const CEGUI::EventArgs& e);
	bool functionLoader7(const CEGUI::EventArgs& e);
	bool functionLoader8(const CEGUI::EventArgs& e);
	bool functionLeftArrow(const CEGUI::EventArgs& e);
	bool functionRightArrow(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;
	void update();

private:
	std::vector<float> positionsX;
	std::vector<float> positionsY;
	float xLeftArrow;
	float yLeftArrow;
	float xRightArrow;
	float yRightArrow;
	float xExtraButton;
	float yExtraButton;

	int posX;
	int posY;
	bool leftArrow = false;
	bool rightArrow = false;

	bool extra = false;

	std::vector<std::string> levels;
	std::vector<CEGUI::Window*> texts;
	std::vector<CEGUI::Window*> records;
	void assignFunctions(int num, std::string name);
	void updateTexts(int num);

	int currentShow;

	float delay;
	float currentTime;
};

#endif

