//////////////////////////////////////////////////////////////////////////
// By Adam Hulbert
// Vector2.cpp
// For AIE Advanced Diploma - Game Math And OpenGL
/////////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include <math.h>
#include <string>

using namespace std;


Vector2::Vector2()
{
	this->x = 1.f;
	this->y = 0.f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2(){}

void Vector2::SetMagnitude(float length)
{
	float angle = this->GetAngle();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

const float Vector2::GetMagnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

//Radians (between -pi and pi)
void Vector2::SetAngle(float angle)
{
	float length = this->GetMagnitude();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

float Vector2::GetAngle()
{
	return atan2(this->y, this->x);
}

//overloaded operators
Vector2& Vector2::operator+=(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& vec)
{
	this->x *= vec;
	this->y *= vec;
	return *this;
}
Vector2& Vector2::operator/=(const Vector2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}
bool Vector2::operator!=(const Vector2& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return false;
	return true;
}

bool Vector2::operator==(const Vector2& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return true;
	return false;
}

void Vector2::operator=(Vector2 vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

Vector2 Vector2::operator-(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	return temp;
}

Vector2 Vector2::operator+(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x + vec.x;
	temp.y = this->y + vec.y;
	return temp;
}

void Vector2::Normalise()
{
	float mag = this->GetMagnitude();
	x /= mag;
	y /= mag;	
}

Vector2 
Vector2::GetNormal()
{
	Vector2 normal(x, y);
	normal.Normalise();
	return normal;
}

Vector2 Vector2::operator*(float vec)
{
	Vector2 temp;
	temp.x = this->x * vec;
	temp.y = this->y * vec;
	return temp;
}

Vector2 Vector2::operator*(Vector2 vec)
{
	vec.x = this->x * vec.x;
	vec.y = this->y * vec.y;
	return vec;
}

Vector2 Vector2::operator/(float scalar_)
{
	Vector2 ret; 
	ret.x = this->x / scalar_;
	ret.y = this->y / scalar_;
	return ret;
}

bool Vector2::operator>(float vec)
{
	return this->GetMagnitude() > vec;
}

Vector2 Vector2::Rotate90(bool clockwise)
{
	Vector2 ret;
	if ( clockwise )
		ret = Vector2( this->y, -this->x );
	else
		ret = Vector2( -this->y, this->x );
	return ret;
}

std::ostream& operator<<(std::ostream& os, Vector2 obj)
{
	os << "X: " << obj.x << ", Y: " << obj.y; 
	return os;
}

Vector2 Vector2::Lerp(Vector2 origin, Vector2 velocity, float scalar)	//scalar between 0 - 1
{
	velocity = velocity * scalar;
	origin += velocity;
	return origin;
}


Vector3::Vector3() : x(0.0), y(0.0), z(0.0){}
Vector3::Vector3(float x_, float y_, float z_): x(x_), y(y_), z(z_){}

float Vector3::GetAngle()
{
	return atan2(this->y, this->x);
}

void Vector3::SetAngle(float angle)
{
	float length = this->GetMagnitude();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

const float Vector3::GetMagnitude()
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Normalise()
{
	float mag = this->GetMagnitude();
	x /= mag;
	y /= mag;	
	z /= mag;	
}



Vector3 Vector3::operator*(float scalar_)
{
	Vector3 ret; 
	ret.x = this->x * scalar_;
	ret.y = this->y * scalar_;
	ret.z = this->z * scalar_;
	return ret;
}



void Vector3::operator+=(Vector3 vec_)
{
	this->x += vec_.x;
	this->y += vec_.y;
	this->z += vec_.z;
}

Vector3 Vector3::operator-(Vector3 vec_)
{
	Vector3 temp;
	temp.x = this->x - vec_.x;
	temp.y = this->y - vec_.y;
	temp.z = this->z - vec_.z;
	return temp;
}

float Vector3::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

string Vector3::ToString()
{
	string ret = "";

	ret += "x: " + to_string(x) + 
		"\ty: " + to_string(y) +
		"\tz: " + to_string(z);

	return ret;
}