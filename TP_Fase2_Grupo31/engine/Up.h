#pragma once

class Up {
private:
	float x;
	float y;
	float z;

public:
	Up();
	Up(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float x);
	void setZ(float x);
};