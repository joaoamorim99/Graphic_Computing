#include "Scale.h";

Scale :: Scale() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Scale :: Scale(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Scale :: getX() {
	return this->x;
}

float Scale :: getY() {
	return this->y;
}

float Scale :: getZ() {
	return this->z;
}

void Scale :: setX(float x) {
	this->x = x;
}


void Scale :: setY(float y) {
	this->y = y;
}

void Scale :: setZ(float z) {
	this->z = z;
}
