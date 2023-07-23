#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"
#include "Camera.h"
#include <vector>
#include "Vertex.h"
#include <fstream>


using namespace std;

using namespace tinyxml2;

vector<string> readXML(const char* file,  Camera* camera);

vector<Vertex> lerFicheiro3d(string file3d);