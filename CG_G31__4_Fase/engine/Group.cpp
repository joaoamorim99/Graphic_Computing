#include "Group.h"

Group::Group() { 

	this->diffuse = Vertex(200 / 255, 200 / 255, 200 / 255);
	this->ambient = Vertex(50 / 255, 50 / 255, 50 / 255);
	this->specular = Vertex(0, 0, 0);
	this->ambient = Vertex(0, 0, 0);
	this->shininess = 128; 
}

Group::Group(vector<Vertex> vertices, vector<int> indices) {
	for (int i = 0; i < vertices.size(); i++) this->vertices.push_back(vertices.at(i));
	for (int i = 0; i < indices.size(); i++) this->indices.push_back(indices.at(i));
	this->diffuse = Vertex(200 / 255, 200 / 255, 200 / 255);
	this->ambient = Vertex(50 / 255, 50 / 255, 50 / 255);
	this->specular = Vertex(0, 0, 0);
	this->ambient = Vertex(0, 0, 0);
	this->shininess = 128;
}

vector<string> Group :: getFiles3d() {
	return this->files3d;
}

string Group::getFile3d(int id) {
	return this->files3d.at(id);
}

vector<string> Group::getImagens() {
	return this->imagens;
}

string Group::getImagem(int id) {
	return this->imagens.at(id);
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

vector<Vertex> Group::getNormais() {
	return this->normais;
}


Vertex Group::getNormal(int id) {
	return this->normais.at(id);
}

vector<Vertex> Group::getTexturas() {
	return this->texturas;
}


Vertex Group::getTextura(int id) {
	return this->texturas.at(id);
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

Vertex Group::getDiffu() {
	return this->diffuse;
}

Vertex Group::getAmbi() {
	return this->ambient;
}

Vertex Group::getSpec() {
	return this->specular;
}

Vertex Group::getEmiss() {
	return this->emissive;
}

float Group::getShini() {
	return this->shininess;
}


void Group::addFile3d(string file) {
	this->files3d.push_back(file);
}

void Group::addImagem(string file) {
	this->imagens.push_back(file);
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

void Group::addNormais(vector<Vertex> n) {
	for (int i = 0; i < n.size(); i++) {
		this->normais.push_back(n.at(i));
	}
}

void Group::addTexturas(vector<Vertex> n) {
	for (int i = 0; i < n.size(); i++) {
		this->texturas.push_back(n.at(i));
	}
}

void Group::addFilho(Group filho) {
	this->filhos.push_back(filho);
}

void Group::addIndices(int index) {
	this->indices.push_back(index);
}


void Group::setDiffu(float r, float g, float b) {
	this->diffuse = Vertex(r, g, b);
}
void Group::setSpec(float r, float g, float b) {
	this->specular = Vertex(r, g, b);
}
void Group::setAmbi(float r, float g, float b) {
	this->ambient = Vertex(r, g, b);
}
void Group::setEmiss(float r, float g, float b) {
	this->emissive = Vertex(r, g, b);
}
void Group::setShini(float value) {
	this->shininess = value;
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



