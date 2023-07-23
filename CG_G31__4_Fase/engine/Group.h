#pragma once


#include "Transform.h"
#include "Illumination.h"
#include <vector>
#include "Vertex.h"
#include <iostream>

using namespace std;

class Group {
private:
    vector<string> files3d;
    vector<Transform> transformacoes;
    Vertex diffuse;
    Vertex ambient;
    Vertex specular;
    Vertex emissive;
    float shininess;
    vector<Vertex> vertices;
    vector<Vertex> normais;
    vector<Group> filhos;
    vector<unsigned int> indices;
    vector<string> imagens;
    vector<Vertex> texturas;

public:
    Group();
    Group(vector<Vertex> vertices, vector<int> indices);
    vector<string> getFiles3d();
    string getFile3d(int id);
    vector<string> getImagens();
    string getImagem(int id);
    vector<Transform> getTranforms();
    Transform getTranform(int id);
    vector<Vertex> getVertexs();
    Vertex getVertex(int id);
    vector<Vertex> getNormais();
    Vertex getNormal(int id);
    vector<Vertex> getTexturas();
    Vertex getTextura(int id);
    vector<Group> getFilhos();
    Group getFilho(int id);
    vector<unsigned int> getIndices();
    Vertex getDiffu();
    Vertex getAmbi();
    Vertex getSpec();
    Vertex getEmiss();
    float getShini();

    void addFile3d(string file);
    void addImagem(string file);
    void addTransform(vector<Transform> t);
    void addVertices(vector<Vertex> v);
    void addNormais(vector<Vertex> n);
    void addTexturas(vector<Vertex> t);
    void addFilho(Group filho);
    void addIndices(int index);
    void setDiffu(float r, float g, float b);
    void setAmbi(float r, float g, float b);
    void setSpec(float r, float g, float b);
    void setEmiss(float r, float g, float b);
    void setShini(float value);
    void print();
};