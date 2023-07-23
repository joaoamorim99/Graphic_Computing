#pragma once

class Translate {
private:
	float x;
	float y;
	float z;


public:
	Translate();
	Translate(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

};