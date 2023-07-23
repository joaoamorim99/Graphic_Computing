#include "Rotate.h";

Rotate :: Rotate() {
	this->angle = 0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Rotate :: Rotate(float angle, float x, float y, float z) {
	this->angle = angle;
	this->x = x;
	this->y = y;
	this->z = z;
}

float Rotate :: getAngle() {
	return this->angle;
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


void Rotate :: setAngle(float angle) {
	this->angle = angle;
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

