#include "Illumination.h"

Illumination::Illumination() {
    this->rgb = Vertex();
    this->value = 0.0f;
}

float Illumination::getValue() {
    return this->value;
}

Vertex Illumination::getRGB() {
    return this->rgb;
}

void Illumination::setValue(float value) {
    this->value = value;
}

void Illumination::setRGB(float x, float y, float z) {
    this->rgb.setVertexX(x);
    this->rgb.setVertexY(y);
    this->rgb.setVertexZ(z);
}