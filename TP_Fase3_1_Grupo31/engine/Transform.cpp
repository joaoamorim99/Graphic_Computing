#include "Transform.h"

Transform::Transform() {
    this->scale = Scale();
    this->translate = Translate();
    this->rotate = Rotate();
    this->flagS = 0;
    this->flagR = 0;
    this->flagT = 0;
    this->flagP = 0;
}

int Transform :: getFlagS() {
    return this->flagS;
}

int Transform::getFlagR() {
    return this->flagR;
}

int Transform::getFlagT() {
    return this->flagT;
}

int Transform::getFlagP() {
    return this->flagP;
}

Scale Transform::getScale() {
    return this->scale;
}

Translate Transform::getTranslate() {
    return this->translate;
}

Rotate Transform::getRotate() {
    return this->rotate;
}




void Transform::setScale(float x, float y, float z) {
    this->scale.setX(x);
    this->scale.setY(y);
    this->scale.setZ(z);
    this->flagS = 1;
}

void Transform::setTranslate(float time, bool allign) {
    this->translate.setTime(time);
    this->translate.setAllign(allign);
    this->flagT = 1;
}

void Transform::setRotate(float var, float x, float y, float z) {
    this->rotate.setVar(var);
    this->rotate.setX(x);
    this->rotate.setY(y);
    this->rotate.setZ(z);
    this->flagR = 1;
}

void Transform::addTranslate(Translate t) {
    this->translate = t;
    this->flagT = 1;
}
