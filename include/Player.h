#pragma once

#include "gameobject.h"
#include "SpitObserver.h"

class Player :
	public GameObject
{
public:
	Player(void);
	~Player(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void RegisterSpitObserver(SpitObserver* spitObserver_);

private:
	unsigned int sprite;

	double mouseX;
	double mouseY;
	SpitObserver* spitObserver;

	float timeSinceLoogie;
};

