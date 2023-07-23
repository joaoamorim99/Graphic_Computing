#pragma once
#include <math.h>
#include <vector>
#include "Vertex.h"
#include "Group.h"

void buildRotMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normalize(float* a);
float length(float* v);
void multMatrixVector(float* m, float* v, float* res);
void getGlobalCatmullRomPoint(float gt, int numpontos, float** p, float* pos, float* deriv);
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);
Group generateBezierPatches(std::vector<Vertex> pVertices, std::vector<size_t> pIndexes, size_t t);

