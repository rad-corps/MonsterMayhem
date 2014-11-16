//////////////////////////////////////////////////////////////////////////
// 
// By Adam Hulbert
// Vector2.h
// For AIE Advanced Diploma - Game Math And OpenGL
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <ostream>
#include <string>

using namespace std;

class Vector2
{
public: 
	//constructor/destructor
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	//Angle Helpers
	void SetAngle(float angle);
	float GetAngle();
	
	//Magnitude
	void SetMagnitude(float length);
	const float GetMagnitude();
	
	//Linear Interpolation
	static Vector2 Lerp(Vector2 origin, Vector2 velocity, float scalar);	//scalar between 0 - 1

	//Rotation helper
	Vector2 Rotate90(bool clockwise);

	//Normalisation Methods
	void Normalise();
	Vector2 GetNormal();
	
	//overloaded operators
	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator/=(const Vector2& vec);
	void operator=(Vector2 vec); //ok
	Vector2 operator-(Vector2 vec);
	Vector2 operator+(Vector2 vec);
	Vector2 operator*(Vector2 vec);
	

	//scalar multiplication
	Vector2& operator*=(const float& vec);
	Vector2 operator*(float vec);
	Vector2 operator/(float vec);
	
	//comparison
	bool operator > (float vec);
	bool operator!=(const Vector2& vec);
	bool operator==(const Vector2& vec);

	float x;
	float y;
};

std::ostream& operator<<(std::ostream& os, Vector2 obj);