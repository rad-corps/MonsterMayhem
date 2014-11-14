#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(void)
{
	cout << "GameObject" << endl;
}


GameObject::~GameObject(void)
{
	cout << "~GameObject" << endl;
}

bool GameObject::IsActive()
{
	return active;
}

Vector2 GameObject::Pos()
{
	return pos;
}

float GameObject::Width()
{
	return width;
}
float GameObject::Height()
{
	return height;
}