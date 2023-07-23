#pragma once


#include "../../../Transform.h"
#include <vector>
#include "../../../Vertex.h"
#include <iostream>

using namespace std;

class Group {
private:
    vector<string> files3d;
    vector<Transform> transformacoes;
    vector<Vertex> vertices;
    vector<Group> filhos;

public:
    Group();
    vector<string> getFiles3d();
    string getFile3d(int id);
    vector<Transform> getTranforms();
    Transform getTranform(int id);
    vector<Vertex> getVertexs();
    Vertex getVertex(int id);
    vector<Group> getFilhos();
    Group getFilho(int id);

    void addFile3d(string file);
    void addTransform(vector<Transform> t);
    void addVertices(vector<Vertex> v);
    void addFilho(Group filho);
    void print();
};