#include "Rotate.h";

Rotate :: Rotate() {
	this->var = 0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Rotate :: Rotate(float var, float x, float y, float z) {
	this->var = var;
	this->x = x;
	this->y = y;
	this->z = z;
}

float Rotate :: getVar() {
	return this->var;
}

float Rotate :: getX() {
	return this->x;
}

float Rotate :: getY() {
	return this->y;
}

float Rotate :: getZ() {
	return this->z;
}


void Rotate :: setVar(float var) {
	this->var = var;
}

void Rotate :: setX(float x) {
	this->x = x;
}


void Rotate :: setY(float y) {
	this->y = y;
}

void Rotate :: setZ(float z) {
	this->z = z;
}

