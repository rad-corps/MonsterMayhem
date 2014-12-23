//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Player.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "gameobject.h"
#include "SpitObserver.h"
#include "PlayerObserver.h"
#include "PowerUp.h"

class Player :
	public GameObject
{
public:
	Player(Vector2 pos_);
	Player();
	~Player(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void SetPlayerPos(int tileX_, int tileY_);

	void UpdateXMovement(float delta_);
	void UpdateYMovement(float delta_);

	void RegisterSpitObserver(SpitObserver* spitObserver_);
	void RegisterPlayerObserver(PlayerObserver* playerObserver_);
	void SetInMud( bool inMud );

	void EatPowerUp(PowerUp& powerUp);

	void UndoUpdate();

private:
	void CalcGUIBars();

	unsigned int sprite;

	double mouseX;
	double mouseY;
	SpitObserver* spitObserver;
	PlayerObserver* playerObserver;
	Vector2 direction;

	float animationTimer;

	float timeSinceLoogie;
	float speed;
	float loogieReload;

	PLAYER_STATUS status;
	PLAYER_ANIMATION animation;
	//allow undo for fence/terrain collision
	Vector2 previousPos;

	bool inMud;
};

