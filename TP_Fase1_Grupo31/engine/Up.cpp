#include "Up.h"


Up::Up()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Up::Up(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Up::getX()
{
	return this->x;
}

float Up::getY()
{
	return this->y;
}

float Up::getZ()
{
	return this->z;
}

void Up::setX(float x)
{
	this->x = x;
}

void Up::setY(float y)
{
	this->y = y;
}

void Up::setZ(float z)
{
	this->z = z;
}