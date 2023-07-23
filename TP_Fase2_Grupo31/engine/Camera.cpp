#include "Camera.h"



Camera::Camera() {
    this->position = Position();
    this->lookAt = LookAt();
    this->up = Up();
    this->projection = Projection();

}

Position Camera :: getPosition() {
    return this->position;
}

LookAt Camera :: getLookAt() {
    return this->lookAt;
}

Up Camera :: getUp() {
    return this->up;
}

Projection Camera :: getProjection() {
    return this->projection;
}

void Camera :: setPosition(float x, float y, float z) {
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
}

void Camera :: setLookAt(float x, float y, float z) {
    this->lookAt.setX(x);
    this->lookAt.setY(y);
    this->lookAt.setZ(z);
}

void Camera :: setUp(float x, float y, float z) {
    this->up.setX(x);
    this->up.setY(y);
    this->up.setZ(z);
}

void Camera :: setProjection(float fov, float near, float far) {
    this->projection.setFov(fov);
    this->projection.setNear(near);
    this->projection.setFar(far);
}

