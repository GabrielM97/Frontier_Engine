#pragma once
#include "Entity.h"
#include <ctime>




class PlayerEntity :public Entity
{
public:
	PlayerEntity();
	PlayerEntity(std::string playerName, int hp,  Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h, int c_id);
	 
	void CreateCollisionBox(int x, int y, int width, int height);
	void const Render(Graphics * g);
	void Update();
	virtual ~PlayerEntity();
	void setPosition();
	void setprevPosition(Vector2D prevpos) { prevPosition = prevpos; };
	void SetSpeed(float UpdatedSpeed);
	void SetDirection(Direction dir) { direction = dir; };
	void AddSpriteSheetId(std::string name);
	void gainEXP(int experience);
	Vector2D GetPosition() { return position;  };
	Type GetType() { return entityType; };
	bool GetLevelUP() { return levelup; };
	int GetLevel() { return lvl; };
	int GetExp() { return exp; };
	int GetExpToNextLevel() { return expToNextLvl; };

	
	

private:
	int exp{ 0 };
	int expToNextLvl{50};
	int lvl{1};
	bool levelup = { false };
	
	
};

