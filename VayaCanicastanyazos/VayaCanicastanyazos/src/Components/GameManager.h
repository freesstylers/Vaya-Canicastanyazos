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
	float getLevelTime();
	float getTimeFromLevel(int level);

private:
	GameManager();
	static GameManager* instance;
	virtual bool ReceiveEvent(Event& event) override;
	std::map <std::string, LevelInfo> levels;
	std::string updateIngameText(float ingameTime);
	int stars_ = 0;
	float levelTime = 0;
	bool paused_ = false;
	bool inLevel_ = false;
};

#endif // !GAMEMANAGER_H
