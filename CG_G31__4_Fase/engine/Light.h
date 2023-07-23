#pragma once
#include <string>

using namespace std;

class Light {
private:
	float var;
	float dirX;
	float dirY;
	float dirZ;

public:
	Light();
	Light(float var, float dirX, float dirY, float dirZ);
	float getVar();
	float getDirX();
	float getDirY();
	float getDirZ();;
	void setVar(float var);
	void setDirX(float dirX);
	void setDirY(float dirY);
	void setDirZ(float dirZ);
};