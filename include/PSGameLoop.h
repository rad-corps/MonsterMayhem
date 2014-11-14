#pragma once

#include "ProgramState.h"
#include "Player.h"
#include "Terrain.h"
#include "SpitObserver.h"
#include "Spit.h"
#include "Monster.h"
#include "PowerUp.h"

class PSGameLoop :
	public ProgramState, public SpitObserver
{
public:
	PSGameLoop(void);
	virtual ~PSGameLoop(void);

	//implementations for ProgramState interface
	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	//implementation of SpitObserver interface
	virtual void SpitEvent(Vector2 position_, float rotation_, float activeTime_); 

private:
	Player player;
	Terrain terrain;
	vector<Spit> spitList;
	vector<Monster> monsterList;
	vector<PowerUp> powerUpList;
};

