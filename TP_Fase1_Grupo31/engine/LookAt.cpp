#include "LookAt.h"


LookAt::LookAt()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

LookAt::LookAt(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float LookAt::getX()
{
	return this->x;
}

float LookAt::getY()
{
	return this->y;
}

float LookAt::getZ()
{
	return this->z;
}

void LookAt::setX(float x)
{
	this->x = x;
}

void LookAt::setY(float y)
{
	this->y = y;
}

void LookAt::setZ(float z)
{
	this->z = z;
}