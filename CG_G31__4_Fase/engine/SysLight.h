#pragma once

#include "../../../Light.h"
#include <string>
#include <vector>

using namespace std;

class SysLight {
private:
	vector<Light> lights;

public:
	SysLight();
	vector<Light> getLights();
	void addLight(string type, float dirX, float dirY, float dirZ);
};