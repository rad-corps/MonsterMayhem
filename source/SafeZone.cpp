#include "SafeZone.h"
#include "AIE.h"
#include "FileSettings.h"


SafeZone::SafeZone(void)
{
	width = FileSettings::GetInt("SAFE_ZONE_W");
	height = FileSettings::GetInt("SAFE_ZONE_H");
	pos = Vector2(FileSettings::GetFloat("SAFE_ZONE_X"), FileSettings::GetFloat("SAFE_ZONE_Y"));
	sprite = CreateSprite("./images/Safe_Zone.png", width, height, false);
}


SafeZone::~SafeZone(void)
{
}

void SafeZone::Update(float delta_)
{}

void SafeZone::Draw()
{
	MoveSprite(sprite, pos.x, pos.y);
	DrawSprite(sprite);
}
