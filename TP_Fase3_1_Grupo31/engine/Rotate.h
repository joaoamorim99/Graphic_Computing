#pragma once
class Rotate {
	private:
		float var;
		float x;
		float y;
		float z;

	public:
		Rotate();
		Rotate(float var, float x, float y, float z);
		float getVar();
		float getX();
		float getY();
		float getZ();;
		void setVar(float var);
		void setX(float x);
		void setY(float y);
		void setZ(float z);
};