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


using namespace std;

using namespace tinyxml2;

Group readXML(const char* file,  Camera* camera);

vector<Vertex> lerFicheiro3d(string file3d);