#include "SysLight.h"

SysLight::SysLight() {}


vector<Light> SysLight::getLights() {
    return this->lights;
}


void SysLight::addLight(string var, float dirX, float dirY, float dirZ) {
    if (var.compare("directional") == 0) this->lights.push_back(Light(0.0, dirX, dirY, dirZ));
    else this->lights.push_back(Light(1.0, dirX, dirY, dirZ));
}

