#include "Light.h";


using namespace std;

Light::Light() {
	this->var = 0;
	this->dirX = 0;
	this->dirY = 0;
	this->dirZ = 0;
}

Light::Light(float var, float dirX, float dirY, float dirZ) {
	this->var = var;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

float Light::getVar() {
	return this->var;
}

float Light::getDirX() {
	return this->dirX;
}

float Light::getDirY() {
	return this->dirY;
}

float Light::getDirZ() {
	return this->dirZ;
}


void Light::setVar(float var) {
	this->var = var;
}

void Light::setDirX(float dirX) {
	this->dirX = dirX;
}


void Light::setDirY(float dirY) {
	this->dirY = dirY;
}

void Light::setDirZ(float dirZ) {
	this->dirZ = dirZ;
}

