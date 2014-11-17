#pragma once

#include "Vector.h"
#include "GameObject.h"
#include "Enums.h"

class GameGUI : public GameObject
{
public:
	GameGUI(void);
	~GameGUI(void);

	//must be called before draw
	void SetGameState(GAME_LOOP_STATE state_);

	virtual void Update(float delta_);
	virtual void Draw();

private:

	//sprites
	unsigned int sprBegWave;
	unsigned int sprEndWave;
	unsigned int sprDigit[10];

	Vector2 sprEndPos;
	Vector2 sprBegPos;

	GAME_LOOP_STATE state;
};

