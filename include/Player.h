#pragma once

#include "gameobject.h"
#include "SpitObserver.h"
#include "PlayerObserver.h"
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
	void RegisterPlayerObserver(PlayerObserver* playerObserver_);

	void EatPowerUp(PowerUp& powerUp);

	void UndoUpdate();

private:
	void CalcGUIBars();

	unsigned int sprite;

	double mouseX;
	double mouseY;
	SpitObserver* spitObserver;
	PlayerObserver* playerObserver;

	float timeSinceLoogie;
	float speed;
	float loogieReload;


	//allow undo for fence/terrain collision
	Vector2 previousPos;
};

