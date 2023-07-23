#include "Transform.h"

Transform::Transform() {
    this->scale = Scale();
    this->translate = Translate();
    this->rotate = Rotate();
    this->flagS = 0;
    this->flagR = 0;
    this->flagT = 0;
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

void Transform::setTranslate(float x, float y, float z) {
    this->translate.setX(x);
    this->translate.setY(y);
    this->translate.setZ(z);
    this->flagT = 1;
}

void Transform::setRotate(float angle, float x, float y, float z) {
    this->rotate.setAngle(angle);
    this->rotate.setX(x);
    this->rotate.setY(y);
    this->rotate.setZ(z);
    this->flagR = 1;
}
