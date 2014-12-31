//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// FrameworkHelpers.h
/////////////////////////////////////////////////////////////////////////

#pragma once
#include "AIE.h"
#include "Vector.h"
#include <string>

//[0][0] -1 when pointing up && +1 when pointing down
//[0][1] +1 when pointing right && -1 when pointing left
//[1][1] +1 when pointing down && -1 when pointing up 
//[1][0] +1 pointing left && -1 pointing right
//radians expressed from -1pi to pi
void RotateSpriteToAngle(const unsigned int& sprite, float radians);
void GetSpriteAngleVector(const unsigned int& sprite, float& x, float& y);
void GetSpriteAngleVector( const unsigned int& sprite, Vector2& vec );

//takes a normalised 2D vector and returns the radians (between -pi and pi)
float GetRadiansFromVector(Vector2& vec );
void RotateSpriteToVector(const unsigned int& sprite, Vector2& vec );

int RandomNumber(int from, int to);
float RandomPercentage(); // between 0 and 1

std::string FloatToPerc(float);

float Lerp(float startRange, float endRange, float num); //num between 0 and 1

void DrawRightAlignedString(const char* text, int xPos, int yPos, int numChars, float fSize, SColour colour);

void GetMouseLocationEx(double& mouseX_, double& mouseY_, const int& screenHeight_);

Vector2 GetGameObjectScreenPosition( Vector2 pos_ );
Vector2 GetGameObjectActualPosition( Vector2 screenPos_ );


//Move Sprite to absolute position (useful for GUI elements that should be unneffected by camera position)
void MoveSpriteAbs(unsigned int sprite_, float posX_, float posY_);
void DrawStringAbs(const char * str_, int x_, int y_ );

float subtractSmallerNumber(float num1_, float num2_);

void DrawIfOnScreen(unsigned int sprite, float xPos, float yPos);

