#pragma once
#include "Entity.h"
#include "..\Physics\Physics.h"



class PlayerEntity :public Entity
{
public:
	PlayerEntity();
	PlayerEntity(std::string playerName, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h, int c_id);
	 
	void CreateCollisionBox(int x, int y, int width, int height);
	void const Render(Graphics * g);
	void Update();
	virtual ~PlayerEntity();
	void setPosition();
	void setprevPosition(Vector2D prevpos) { prevPosition = prevpos; };
	void SetSpeed(float UpdatedSpeed);
	void SetDirection(Direction dir) { playerDirection = dir; };
	void SetState(State state) { playerState = state; };
	State GetState() { return playerState; };
	void AddSpriteSheetId(std::string name);
	Vector2D GetPosition() { return position;  };
	Type GetType() { return entityType; };
	
	

private:
	Physics *physics;
	int walkSpeed_, sprintSpeed_, activeSpriteSheet;
	Direction playerDirection;
	State playerState;
	Vector2D prevPosition;
	vector<std::string> spriteId;
	
	 
	
};

