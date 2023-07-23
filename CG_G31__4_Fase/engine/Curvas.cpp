#include "Curvas.h"
#include <vector>
#include <iostream>

float catmullMatrix[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
								{ 1.0f, -2.5f,  2.0f, -0.5f },
								{ -0.5f,  0.0f,  0.5f,  0.0f },
								{ 0.0f,  1.0f,  0.0f,  0.0f } 
};

float bezierMatrix[4][4] = { { -1.0f, 3.0f, -3.0f, 1.0f },
							   { 3.0f, -6.0f, 3.0f, 0.0f },
							   { -3.0f, 3.0f, 0.0f, 0.0f },
							   { 1.0f,  0.0f, 0.0f, 0.0f } 
};


void buildRotMatrix(float* x, float* y, float* z, float* m)
{
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


float length(float* v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}


void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {


	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };


	for (int i = 0; i < 3; i++) {	 // i = x, y, z
		float p[4] = { p0[i], p1[i], p2[i], p3[i] };
		float a[4];
		multMatrixVector(*m, p, a);

		pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3];
		
		deriv[i] = 3 * powf(t, 2.0) * a[0] + 2 * t * a[1] + a[2];
	}
}

void getGlobalCatmullRomPoint(float gt, int numpontos, float** p, float* pos, float* deriv) {
	float t = gt * numpontos; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + numpontos - 1) % numpontos; 
	indices[1] = (indices[0] + 1) % numpontos;
	indices[2] = (indices[1] + 1) % numpontos;
	indices[3] = (indices[2] + 1) % numpontos;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}



void getBezierPoint(float u, float v,
	float** pMatrixX, float** pMatrixY, float** pMatrixZ,
	float* pos)
{

	float uVec[4] = { u * u * u, u * u, u, 1 };
	float vVec[4] = { v * v * v, v * v, v, 1 };

	float mvVec[4];
	float px[4];
	float py[4];
	float pz[4];

	float mx[4];
	float my[4];
	float mz[4];


	multMatrixVector((float*)bezierMatrix, vVec, mvVec);
	multMatrixVector((float*)pMatrixX, mvVec, px);
	multMatrixVector((float*)pMatrixY, mvVec, py);
	multMatrixVector((float*)pMatrixZ, mvVec, pz);

	multMatrixVector((float*)bezierMatrix, px, mx);
	multMatrixVector((float*)bezierMatrix, py, my);
	multMatrixVector((float*)bezierMatrix, pz, mz);


	pos[0] = (uVec[0] * mx[0]) + (uVec[1] * mx[1]) + (uVec[2] * mx[2]) + (uVec[3] * mx[3]);
	pos[1] = (uVec[0] * my[0]) + (uVec[1] * my[1]) + (uVec[2] * my[2]) + (uVec[3] * my[3]);
	pos[2] = (uVec[0] * mz[0]) + (uVec[1] * mz[1]) + (uVec[2] * mz[2]) + (uVec[3] * mz[3]);
}


/*
 * A partir dos vetores de vértices e índices, gera os pontos
 * correspondentes às patches de Bezier.
 */
Group generateBezierPatches(std::vector<Vertex> pVertices,
	std::vector<size_t> pIndexes,
	size_t t)
{
	vector<Vertex> vertices;
	vector<int> indexes;
	size_t i = 0;
	size_t j = 0;
	size_t w = 0;
	size_t z = 0;
	size_t start = 0;
	size_t index = 0;
	size_t patch = 0;

	float u = 0.0f;
	float v = 0.0f;

	float pos[3];
	float pMatrixX[4][4];
	float pMatrixY[4][4];
	float pMatrixZ[4][4];


	for (start = 0; start < pIndexes.size(); start += 16) {
		for (i = 0; i <= t; i++) {
			u = ((float)i) / ((float)t);

			for (j = 0; j <= t; j++) {
				v = ((float)j) / ((float)t);

				for (w = 0; w < 4; w++) {
					for (z = 0; z < 4; z++) {
						pMatrixX[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getVertexX();
						pMatrixY[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getVertexY();
						pMatrixZ[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getVertexZ();
					}
				}

				getBezierPoint(u, v, (float**)pMatrixX, (float**)pMatrixY, (float**)pMatrixZ, pos);

				vertices.push_back(Vertex(pos[0], pos[1], pos[2]));
			}
		}
	}

	for (start = 0; start < pIndexes.size() / 16; start++) {
		patch = (t + 1) * (t + 1) * start;

		for (i = 0; i < t; i++) {
			for (j = 0; j < t; j++) {
				indexes.push_back(patch + ((t + 1) * i) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j + 1);
				indexes.push_back(patch + ((t + 1) * i) + j + 1);

				indexes.push_back(patch + ((t + 1) * i) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j + 1);
			}
		}
	}

	return Group(vertices, indexes);
}