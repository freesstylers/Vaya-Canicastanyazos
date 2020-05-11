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

	int getStars();
	void addStars(int s);
	void resetStars();
	void saveData(std::string);
	void readData();
private:
	GameManager();
	static GameManager* instance;
	virtual bool ReceiveEvent(Event& event) override;
	std::map <std::string, LevelInfo> levels;
	int stars_ = 0;
	float time = 0;

};

#endif // !GAMEMANAGER_H
