//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// FrameworkHelpers.cpp
/////////////////////////////////////////////////////////////////////////

//originally written for Geo/Final Defence by Adam Hulbert.

#include "AIE.h"
#include "Vector.h"
#include <math.h>
#include <cstdlib>
#include "FrameworkHelpers.h"
#include <time.h>
#include "FileSettings.h"
#include "enums.h"


//[0][0] -1 when pointing up && +1 when pointing down
//[0][1] +1 when pointing right && -1 when pointing left
//[1][1] +1 when pointing down && -1 when pointing up 
//[1][0] +1 pointing left && -1 pointing right
//radians expressed from -1pi to pi
void RotateSpriteToAngle(const unsigned int& sprite, float radians)
{
	float x = cos(radians);
	float y = sin(radians);
	float matrix[4][4];
	GetSpriteMatrix(sprite, matrix[0]);
	matrix[0][0] = x;
	matrix[0][1] = y;
	matrix[1][1] = x;
	matrix[1][0] = -y;
	SetSpriteMatrix(sprite, matrix[0]);
}

//returns the normalised x, y vector coordinates
void GetSpriteAngleVector(const unsigned int& sprite, float& x, float& y)
{
	float matrix[4][4];
	GetSpriteMatrix(sprite, matrix[0]);
	x = matrix[0][0];
	y = matrix[0][1];
}

void GetSpriteAngleVector( const unsigned int& sprite, Vector2& vec )
{
	float x,y;
	GetSpriteAngleVector(sprite, x, y);
	vec.x = x;
	vec.y = y;
}

float GetRadiansFromVector(Vector2& vec)
{
	return atan2(vec.y, vec.x);
}

void RotateSpriteToVector(const unsigned int& sprite, Vector2& vec )
{
	float radians = GetRadiansFromVector(vec);
	RotateSpriteToAngle(sprite, radians);
}

//generate a random number from from to to inclusive
int RandomNumber(int from, int to)
{
	int diff = to - from;
	int result = rand() % diff + from;
	return result;
}

float RandomPercentage()
{
	int res = RandomNumber(0, 100);
	float fres = (float)res / 100.f;
	return fres;
}

void DrawRightAlignedString(const char* text, int xPos, int yPos, int numchars, float fSize, SColour colour)
{
	int text_len = strlen(text);
	int rightX = xPos - text_len * (int)(29.f * fSize);

	DrawString(text, rightX, yPos, fSize, colour);
}

std::string FloatToPerc(float x)
{

	int temp = (int)(x * 100);
	return std::to_string(temp) + "%";
}

float Lerp(float min, float max, float norm) //num between 0 and 1
{
	return (max - min) * norm - min;
}

void GetMouseLocationEx(double& mouseX_, double& mouseY_, const int& screenHeight_)
{
	GetMouseLocation( mouseX_, mouseY_ );
	mouseY_ = screenHeight_ - mouseY_;
}

Vector2 GetGameObjectScreenPosition( Vector2 pos_ )
{
	Vector2 cam;
	float camX, camY;
	GetCameraPosition(camX, camY);
	cam = Vector2(camX, camY);
	return pos_ - cam;
}

Vector2 GetGameObjectActualPosition( Vector2 screenPos_ )
{
	Vector2 cam;
	float camX, camY;
	GetCameraPosition(camX, camY);
	cam = Vector2(camX, camY);
	return cam - screenPos_;
}

void MoveSpriteAbs(unsigned int sprite_, float posX_, float posY_)
{
	float camX, camY;
	GetCameraPosition(camX, camY);
	MoveSprite(sprite_, camX + posX_, camY + posY_);
}

void DrawStringAbs(const char * str_, int x_, int y_ )
{
	float camX, camY;
	GetCameraPosition(camX, camY);
	DrawString(str_, camX + x_, camY + y_);
}

float subtractSmallerNumber(float num1_, float num2_)
{
	if ( num1_ < num2_ )
		return num2_ - num1_;
	return num1_ - num2_;
}

void DrawIfOnScreen(unsigned int sprite, float xPos, float yPos)
{
	float camPosX, camPosY;
	GetCameraPosition(camPosX, camPosY);

	if ( xPos + TERRAIN_W > camPosX && 
		xPos - TERRAIN_W < camPosX + FileSettings::GetInt("SCREEN_W") &&
		yPos + TERRAIN_H > camPosY  && 
		yPos - TERRAIN_H < camPosY + FileSettings::GetInt("SCREEN_H") )
	{
		MoveSprite(sprite, xPos, yPos);
		DrawSprite(sprite);			
	}

}

//void DrawIfOnScreen(unsigned int sprite, float xPos, float yPos)
//{
//	MoveSprite(sprite, xPos, yPos);
//	DrawSprite(sprite);			
//}