#pragma once

class Point {
private:
	float x;
	float y;
	float z;


public:
	Point();
	Point(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

};
