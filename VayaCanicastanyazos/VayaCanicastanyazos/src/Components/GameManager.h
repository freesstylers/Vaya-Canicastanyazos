#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER
#include "Entity/Component.h"

struct LevelInfo
{
	int stars;
	float time;
};
class GameManager : public Component
{
public:
	~GameManager();

	static GameManager* getInstance();
	static void clean();

	void pause();
	bool isPaused();
	virtual void update() override;

	int getStars();
	void addStars(int s);
	void resetStars();
	void saveData(std::string);
	void readData();
	std::map <std::string, LevelInfo> getLevels();

private:
	GameManager();
	static GameManager* instance;
	virtual bool ReceiveEvent(Event& event) override;
	std::map <std::string, LevelInfo> levels;
	int stars_ = 0;
	float time = 0;
	float levelTime = 0;
	bool paused_ = false;
	bool inLevel_ = false;
};

#endif // !GAMEMANAGER_H
