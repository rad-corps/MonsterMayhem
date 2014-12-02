#pragma once
#include "GameObject.h"

class SafeZone : public GameObject
{

public:
	SafeZone(void);
	~SafeZone(void);

	virtual void Update(float delta_);
	virtual void Draw();

private:
	unsigned int sprite;
};

