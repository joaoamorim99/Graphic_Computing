#include "Group.h"

Group :: Group() {}

Group::Group(vector<Vertex> vertices, vector<int> indices) {
	for (int i = 0; i < vertices.size(); i++) this->vertices.push_back(vertices.at(i));
	for (int i = 0; i < indices.size(); i++) this->indices.push_back(indices.at(i));
}

vector<string> Group :: getFiles3d() {
	return this->files3d;
}

string Group::getFile3d(int id) {
	return this->files3d.at(id);
}

vector<Transform> Group::getTranforms() {
	return this->transformacoes;
}

Transform Group::getTranform(int id) {
	return this->transformacoes.at(id);
}

vector<Vertex> Group::getVertexs() {
	return this->vertices;
}


Vertex Group::getVertex(int id) {
	return this->vertices.at(id);
}


vector<Group> Group::getFilhos() {
	return this->filhos;
}

Group Group::getFilho(int id) {
	return this->filhos.at(id);
}

vector<unsigned int> Group::getIndices() {
	return this->indices;
}


void Group::addFile3d(string file) {
	this->files3d.push_back(file);
}

void Group::addTransform(vector<Transform> t) {
	for (int i = 0; i < t.size(); i++) {
		this->transformacoes.push_back(t.at(i));
	}
}

void Group::addVertices(vector<Vertex> v) {
	for (int i = 0; i < v.size(); i++) {
		this->vertices.push_back(v.at(i));
	}
}

void Group::addFilho(Group filho) {
	this->filhos.push_back(filho);
}

void Group::addIndices(int index) {
	this->indices.push_back(index);
}

void Group :: print() {
	for (int i = 0; i < this->files3d.size(); i++) {
		cout << this->files3d.at(i) << endl;
	}
	for (int j = 0; j < this->filhos.size(); j++) {
		cout << "filho" << endl;
		this->filhos.at(j).print();
	}
}

