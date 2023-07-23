#pragma once

class LookAt {
private:
	float x;
	float y;
	float z;

public:
	LookAt();
	LookAt(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float x);
	void setZ(float x);
};