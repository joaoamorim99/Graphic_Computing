#pragma once

class Scale {
	private:
		float x;
		float y;
		float z;

	public:
		Scale();
		Scale(float x, float y, float z);
		float getX();
		float getY();
		float getZ();
		void setX(float x);
		void setY(float y);
		void setZ(float z);
};
