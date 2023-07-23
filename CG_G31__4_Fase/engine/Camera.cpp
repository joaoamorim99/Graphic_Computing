#include "Camera.h"



Camera::Camera() {
    this->position = Vertex();
    this->lookAt = Vertex();
    this->up = Vertex();
    this->projection = Projection();

}

Vertex Camera :: getPosition() {
    return this->position;
}

Vertex Camera :: getLookAt() {
    return this->lookAt;
}

Vertex Camera :: getUp() {
    return this->up;
}

Projection Camera :: getProjection() {
    return this->projection;
}

void Camera :: setPosition(float x, float y, float z) {
    this->position.setVertexX(x);
    this->position.setVertexY(y);
    this->position.setVertexZ(z);
}

void Camera :: setLookAt(float x, float y, float z) {
    this->lookAt.setVertexX(x);
    this->lookAt.setVertexY(y);
    this->lookAt.setVertexZ(z);
}

void Camera :: setUp(float x, float y, float z) {
    this->up.setVertexX(x);
    this->up.setVertexY(y);
    this->up.setVertexZ(z);
}

void Camera :: setProjection(float fov, float near, float far) {
    this->projection.setFov(fov);
    this->projection.setNear(near);
    this->projection.setFar(far);
}

