#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include "Point.h"
#include "Vertex.h"

class Transform {
private:
	Scale scale;
	Translate translate;
	Rotate rotate;
	int flagS;
	int flagT;
	int flagR;
	int flagTN;

public:
	Transform();
	Scale getScale();
	Translate getTranslate();
	Rotate getRotate();
	int getFlagS();
	int getFlagT();
	int getFlagR();
	int getFlagTN();
	void setScale(float x, float y, float z);
	void setTranslate(float time, bool allign);
	void setTranslateVertex(float x, float y, float z);
	void setRotate(float angle, float x, float y, float z);
	void addTranslate(Translate t);
};