#pragma once

#include "gameobject.h"
#include "SpitObserver.h"
#include "PowerUp.h"

class Player :
	public GameObject
{
public:
	Player(void);
	~Player(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void RegisterSpitObserver(SpitObserver* spitObserver_);

	void EatPowerUp(PowerUp& powerUp);

	void UndoUpdate();

private:
	unsigned int sprite;

	double mouseX;
	double mouseY;
	SpitObserver* spitObserver;

	float timeSinceLoogie;
	float speed;
	float loogieReload;


	//allow undo for fence/terrain collision
	Vector2 previousPos;
};

