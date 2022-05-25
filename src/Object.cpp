#include "Object.h"

Object::Object()
{
	rect.x = rect.y = rect.h = rect.w = 0;
}

Object::~Object()
{

}

void Object::init(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Object::move(int x, int y)
{
	rect.x += x;
	rect.y += y;
}