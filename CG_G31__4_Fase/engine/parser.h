#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"
#include "Camera.h"
#include <vector>
#include "Vertex.h"
#include <fstream>
#include "Group.h"
#include "Illumination.h"
#include "SysLight.h"


using namespace std;

using namespace tinyxml2;

Group readXML(const char* file,  Camera* camera, SysLight *light);

vector<Vertex> lerFicheiro3d(string file3d);