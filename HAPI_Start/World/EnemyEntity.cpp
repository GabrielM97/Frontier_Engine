#include "EnemyEntity.h"
#include "..\Graphics\Graphics.h"
#include "..\Physics\Physics.h"
#include "..\AI\AI.h"


EnemyEntity::EnemyEntity(std::string playerName, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int awareRad, int attackRad, int w, int h)
{
	name = playerName;
	position = pos;
	prevPosition = pos;
	walkSpeed_ = walkSpeed;
	sprintSpeed_ = sprintSpeed;
	physics = new Physics();
	isCollidable = true;
	spriteId.push_back(playerName);
	activeSpriteSheet = 0;
	entityType = Type::Enemy;
	width = w;
	height = h;
	health = hp;
	max_health = hp;
	isAlive = true;
	awarnessRadius = awareRad;
	attackRadius = attackRad;
}

EnemyEntity::EnemyEntity(std::string playerName, Type t, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int awareRad, int attackRad, bool alive, int w, int h)
{
	name = playerName;
	position = pos;
	prevPosition = pos;
	walkSpeed_ = walkSpeed;
	sprintSpeed_ = sprintSpeed;
	physics = new Physics();
	isCollidable = true;
	spriteId.push_back(playerName);
	activeSpriteSheet = 0;
	entityType = t;
	width = w;
	height = h;
	health = hp;
	max_health = hp;
	isAlive = alive;
	awarnessRadius = awareRad;
	attackRadius = attackRad;
}

void EnemyEntity::CreateCollisionBox(int x, int y, int width, int height)
{
	collisionBox.left = x;
	collisionBox.top = y;
	collisionBox.right = x + width;
	collisionBox.bottom = y + height;
}

void const EnemyEntity::Render(Graphics * g)
{
	if (state == State::collided)
		position -= (position - prevPosition)*2;

	g->Draw(spriteId.at(activeSpriteSheet), RenderType::TILE, (int)direction, (int)state, position.x, position.y);
	prevPosition = position;
}

void const EnemyEntity::reset()
{
	health = max_health;
	isAlive = true;
	if (entityType == Type::Boss)
	{
		position.setPos(400, 10);
	}else
		position.setPos((rand() % 400) + 200, (rand() % 300) + 200);
}

void EnemyEntity::Update()
{
	CreateCollisionBox((int)position.x, (int)position.y, width, height);
	
	if (HAPI.GetTime() - lasttick >= 100 && entityType == Type::Enemy)
	{

		ai.SetStartPosition(position);
		ai.SetEndPosition(targetPosition);

		switch (eState)
		{
		case enemyState::Roam:
			position = ai.FindPath(walkSpeed_, 4);
			break;
		case enemyState::Alerted:
			position = ai.FindPath(sprintSpeed_, 4);
			break;
		case enemyState::Attacking:
			position = ai.FindPath(sprintSpeed_, 4);
			break;
		default:
			break;
		}

		direction = (Direction)ai.getDir();

		if (position.x >= targetPosition.x - sprintSpeed_ && position.x <= targetPosition.x + sprintSpeed_ &&
			position.y >= targetPosition.y - sprintSpeed_ && position.y <= targetPosition.y + sprintSpeed_)
		{
			targetPosFound = true;

		}
		else
		{
			targetPosFound = false;

		}


		if (state == State::collided)
		{
			targetPosFound = true;


		}

		lasttick = HAPI.GetTime();
	}


	if (HAPI.GetTime() - lasttick >= 100 && entityType == Type::Boss)
	{

		ai.SetStartPosition(position);
		ai.SetEndPosition({targetPosition.x-(width/2), position.y});

		switch (eState)
		{
		case enemyState::Roam:
			position = ai.FindPath(walkSpeed_, 2);
			break;
		case enemyState::Alerted:
			position = ai.FindPath(sprintSpeed_, 2);
			break;
		case enemyState::Attacking:
			position = ai.FindPath(sprintSpeed_, 2);
			break;
		default:
			break;
		}

		//direction = (Direction)ai.getDir();

		if (position.x >= targetPosition.x - sprintSpeed_ && position.x <= targetPosition.x + sprintSpeed_ )
		{
			targetPosFound = true;

		}
		else
		{
			targetPosFound = false;

		}


		if (state == State::collided)
		{
			targetPosFound = true;

		}


		
		cout << health << endl;

		lasttick = HAPI.GetTime();
	}

	
	if (health <= 0)
		isAlive = false;
	
	state = State::moving;
}

void EnemyEntity::isAlerted(Vector2D playerPos)
{
	Vector2D distanceBetweenEnemyAndPlayer = playerPos - position;

	float floatDistance = distanceBetweenEnemyAndPlayer.distance();

	if (floatDistance <= awarnessRadius)
	{
		targetPosition = playerPos;
		eState = enemyState::Alerted;
		eState = enemyState::Attacking;
		state = State::battle;
	}

	if (floatDistance <= attackRadius)
	{
		targetPosition = playerPos;
		eState = enemyState::Attacking;
		state = State::battle;
	}
}

EnemyEntity::~EnemyEntity()
{
	delete physics;
}
