#pragma once

class Vertex {
private:
	float x;
	float y;
	float z;

public :
	Vertex();
	Vertex(float x, float y, float z);
	float getVertexX();
	float getVertexY();
	float getVertexZ();
	void setVertexX(float x);
	void setVertexY(float y);
	void setVertexZ(float z);
};
