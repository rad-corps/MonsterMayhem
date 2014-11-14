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