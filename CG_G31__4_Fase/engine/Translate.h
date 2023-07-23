#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;

class Translate {
private:
	float time;
	bool allign;
	vector<Vertex> point;
	float x;
	float y;
	float z;


public:
	Translate();
	Translate(float time, bool allign, vector<Vertex> points, float x, float y, float z);
	float getTime();
	float getAllign();
	vector<Vertex> getPoint();
	float getX();
	float getY();
	float getZ();
	void setTime(float time);
	void setAllign(bool allign);
	void addPoint(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float** toFloat();
};