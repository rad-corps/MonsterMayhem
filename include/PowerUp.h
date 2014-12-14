#pragma once

#include "GameObject.h"
#include "AIE.h"
#include "Enums.h"
#include "Vector.h"

class PowerUp : public GameObject
{
public:
	PowerUp();
	~PowerUp(void);

	virtual void Update(float delta_);
	virtual void Draw();
	POWER_UP_TYPE Eat();	


	void Spawn(POWER_UP_TYPE type_, Vector2 pos_);

private:
	POWER_UP_TYPE type;
	unsigned int sprite;
};

