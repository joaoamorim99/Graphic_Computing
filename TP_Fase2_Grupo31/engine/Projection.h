#pragma once

class Projection {
private:
	float fov;
	float near;
	float far;

public:
	Projection();
	Projection(float fov, float near, float far);
	float getFov();
	float getNear();
	float getFar();
	void setFov(float x);
	void setNear(float x);
	void setFar(float x);
};