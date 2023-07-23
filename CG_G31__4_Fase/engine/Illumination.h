#pragma once
#include "Vertex.h"

class Illumination {

private:
	Vertex rgb;
	float value;

public:
	Illumination();
	Vertex getRGB();
	float getValue();
	void setValue(float value);
	void setRGB(float x, float y, float z);

};