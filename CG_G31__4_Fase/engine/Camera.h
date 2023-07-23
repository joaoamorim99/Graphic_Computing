#pragma once

#include <../../../LookAt.h>
#include <../../../Up.h>
#include <../../../Projection.h>
#include "Vertex.h"

class Camera {
private:
	Vertex position;
	Vertex lookAt;
	Vertex up;
	Projection projection;

public:
	Camera();
	Vertex getPosition();
	Vertex getLookAt();
	Vertex getUp();
	Projection getProjection();
	void setPosition(float x,float y, float z);
	void setLookAt(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setProjection(float fov, float near, float far);
};