#include "Vertex.h"

Vertex :: Vertex() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vertex :: Vertex(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex :: getVertexX() {
    return this->x;
}

float Vertex :: getVertexY() {
    return this->y;
}

float Vertex :: getVertexZ() {
    return this->z;
}


void  Vertex :: setVertexX(float x) {
    this->x = x;
}

void Vertex :: setVertexY(float y) {
    this->y = y;
}

void Vertex :: setVertexZ(float z) {
    this->z = z;
}
