#pragma once

#include <../../../Position.h>
#include <../../../LookAt.h>
#include <../../../Up.h>
#include <../../../Projection.h>

class Camera {
private:
	Position position;
	LookAt lookAt;
	Up up;
	Projection projection;

public:
	Camera();
	Position getPosition();
	LookAt getLookAt();
	Up getUp();
	Projection getProjection();
	void setPosition(float x,float y, float z);
	void setLookAt(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setProjection(float fov, float near, float far);
};