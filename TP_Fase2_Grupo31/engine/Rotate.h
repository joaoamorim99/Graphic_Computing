#pragma once
class Rotate {
	private:
		float angle;
		float x;
		float y;
		float z;

	public:
		Rotate();
		Rotate(float angle, float x, float y, float z);
		float getAngle();
		float getX();
		float getY();
		float getZ();;
		void setAngle(float angle);
		void setX(float x);
		void setY(float y);
		void setZ(float z);
};