#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
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

Rect GameObject::GetRect()
{
	return Rect(pos, width, height);
}

void GameObject::SetActive(bool active_)
{
	active = active_;
}