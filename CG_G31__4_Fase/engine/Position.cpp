#include "Position.h"


Position::Position()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Position ::Position(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Position::getX()
{
	return this->x;
}

float Position::getY()
{
	return this->y;
}

float Position::getZ()
{
	return this->z;
}

void Position::setX(float x)
{
	this->x = x;
}

void Position::setY(float y)
{
	this->y = y;
}

void Position::setZ(float z)
{
	this->z = z;
}