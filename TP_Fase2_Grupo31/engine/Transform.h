#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"

class Transform {
private:
	Scale scale;
	Translate translate;
	Rotate rotate;
	int flagS;
	int flagT;
	int flagR;

public:
	Transform();
	Scale getScale();
	Translate getTranslate();
	Rotate getRotate();
	int getFlagS();
	int getFlagT();
	int getFlagR();
	void setScale(float x, float y, float z);
	void setTranslate(float x, float y, float z);
	void setRotate(float angle, float x, float y, float z);
};