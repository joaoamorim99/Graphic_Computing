#include "parser.h"

void readXMLCamera(XMLNode* camerazica, Camera* camera) {
	XMLNode* next = camerazica->FirstChild();
	XMLElement* elem = next->FirstChildElement("position");


	camera->setPosition(next->ToElement()->FloatAttribute("x"),
		next->ToElement()->FloatAttribute("y"),
		next->ToElement()->FloatAttribute("z"));


	next = next->NextSiblingElement();

	camera->setLookAt(next->ToElement()->FloatAttribute("x"),
		next->ToElement()->FloatAttribute("y"),
		next->ToElement()->FloatAttribute("z"));

	next = next->NextSiblingElement();

	camera->setUp(next->ToElement()->FloatAttribute("x"),
		next->ToElement()->FloatAttribute("y"),
		next->ToElement()->FloatAttribute("z"));

	next = next->NextSiblingElement();

	camera->setProjection(next->ToElement()->FloatAttribute("fov"),
		next->ToElement()->FloatAttribute("near"),
		next->ToElement()->FloatAttribute("far"));
}

vector<string> readXMLGroup(XMLNode* group) {
	vector<string> aux;
	XMLNode* next = group->FirstChild();

	while (next) {
		if (strcmp(next->Value(), "models") == 0) {
			XMLElement* elem = next->FirstChildElement("model");
			while (elem) {
				aux.push_back(std::string(elem->Attribute("file")));
				elem = elem->NextSiblingElement("model");
			}
		}
		next = next->NextSibling();
	}
	return aux;
}



vector<string> readXML(const char* file, Camera* camera) {
	vector<string> aux;
	XMLDocument doc;
	doc.LoadFile(file);
	
	XMLNode* world = doc.RootElement();
	XMLNode* next = world->FirstChild();

	while (next) {
		if (strcmp(next->Value(), "camera") == 0)
			readXMLCamera(next,camera);
		else
			aux = readXMLGroup(next);

		next = next->NextSibling();
	}
	return aux;
}



vector<Vertex> lerFicheiro3d(string file3d) {
	std :: ifstream file;

	file.open(file3d);

	std::cout << file3d << "\n";

	if (file.fail()) {
		std::cerr << "Erro a abrir o ficheiro\n";
		exit(1);
	}

	vector<Vertex> aux;

	Vertex v;
	float x, y, z;

	file >> x;
	while (file >> x >> y >> z) {
		v = Vertex(x, y, z);
		aux.push_back(v);
	}
	return aux;
}
