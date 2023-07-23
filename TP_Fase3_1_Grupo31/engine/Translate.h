#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;

class Translate {
private:
	float time;
	bool allign;
	vector<Vertex> point;


public:
	Translate();
	Translate(float time, bool allign, vector<Vertex> points);
	float getTime();
	float getAllign();
	vector<Vertex> getPoint();
	void setTime(float time);
	void setAllign(bool allign);
	void addPoint(float x, float y, float z);
	float** toFloat();
};