#include "Projection.h"


Projection::Projection()
{
	this->fov = 0;
	this->near = 0;
	this->far = 0;
}

Projection::Projection(float fov, float near, float far)
{
	this->fov = fov;
	this->near = near;
	this->far = far;
}

float Projection::getFov()
{
	return this->fov;
}

float Projection::getNear()
{
	return this->near;
}

float Projection::getFar()
{
	return this->far;
}

void Projection::setFov(float fov)
{
	this->fov = fov;
}

void Projection::setNear(float near)
{
	this->near = near;
}

void Projection::setFar(float far) {
	this->far = far;
}