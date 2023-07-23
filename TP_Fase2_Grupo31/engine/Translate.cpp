#include "Translate.h";

Translate :: Translate() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Translate :: Translate(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Translate :: getX() {
	return this->x;
}

float Translate :: getY() {
	return this->y;
}

float Translate :: getZ() {
	return this->z;
}

void Translate :: setX(float x) {
	this->x = x;
}

void Translate :: setY(float y) {
	this->y = y;
}

void Translate :: setZ(float z) {
	this->z = z;
}