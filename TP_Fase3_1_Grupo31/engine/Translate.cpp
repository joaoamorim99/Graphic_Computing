#include "Translate.h";



Translate :: Translate() {
	this->time = 0;
	this->allign = false;
}

Translate :: Translate(float time, bool allign, vector<Vertex> points) {
	this->time = time;
	this->allign = allign;
	for (int i = 0; i < points.size(); i++ ) {
		this->point.push_back(points.at(i));
	}
}

float Translate :: getTime() {
	return this->time;
}

float Translate :: getAllign() {
	return this->allign;
}

vector<Vertex> Translate::getPoint() {
	return this->point;
}


void Translate :: setTime(float time) {
	this->time = time;
}

void Translate :: setAllign(bool y) {
	this->allign = y;
}

void Translate::addPoint(float x, float y, float z) {
	Vertex point = Vertex(x, y, z);
	this->point.push_back(point);
}

float** Translate::toFloat() {
	const int size = this->point.size();
	float** p = 0;
	p = new float* [size];
	for (int i = 0; i < this->point.size(); i++) {
		p[i] = new float[3];
		p[i][0] = this->point.at(i).getVertexX();
		p[i][1] = this->point.at(i).getVertexY();
		p[i][2] = this->point.at(i).getVertexZ();
	}
	return p;
}
