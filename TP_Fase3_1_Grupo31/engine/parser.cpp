#include "parser.h"

string aux = "";

void lerFicheiro3d(string file3d, Group* g) {
	std::ifstream file;

	file.open("../testes/" + file3d);

	if (file.fail()) {
		std::cerr << "Erro a abrir o ficheiro\n";
		exit(1);
	}

	vector<Vertex> vertices;

	Vertex v;
	float x, y, z;

	int n, w, i  = 0;

	file >> n;
	while (i < n) {
		file >> x >> y >> z;
		v = Vertex(x, y, z);
		vertices.push_back(v);
		i++;
	} 

	g->addVertices(vertices);
	
	while (file >> w) {
		g->addIndices(w);
	}
}


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

vector<Transform> readXMLTransform(XMLNode* next) {
	vector<Transform> transformers;
	XMLNode* elem = next->FirstChild();
	
	while (elem) {
		Transform t = Transform();
		if (strcmp(elem->Value(), "translate") == 0) {
			Translate translate = Translate();

			translate.setTime(elem->ToElement()->FloatAttribute("time"));
			translate.setAllign(elem->ToElement()->BoolAttribute("allign"));

			XMLElement* elemento;
			elemento = elem->FirstChildElement();

			
			int i = 0;
			while (elemento) {
				if (strcmp(elemento->Value(), "point") == 0) {

					translate.addPoint(elemento->ToElement()->FloatAttribute("x"),
						elemento->ToElement()->FloatAttribute("y"),
						elemento->ToElement()->FloatAttribute("z"));

					i++;
				}

				elemento = elemento->NextSiblingElement();
		
			}
			t.addTranslate(translate);
		}

		

		else if (strcmp(elem->Value(), "rotate") == 0) {

			if (elem->ToElement()->FloatAttribute("time")) {
				aux = "time";

				t.setRotate(elem->ToElement()->FloatAttribute(aux.c_str()),
					elem->ToElement()->FloatAttribute("x"),
					elem->ToElement()->FloatAttribute("y"),
					elem->ToElement()->FloatAttribute("z"));
		}
			
			else if (elem->ToElement()->FloatAttribute("angle")) {
				aux = "angle";
				t.setRotate(elem->ToElement()->FloatAttribute(aux.c_str()),
					elem->ToElement()->FloatAttribute("x"),
					elem->ToElement()->FloatAttribute("y"),
					elem->ToElement()->FloatAttribute("z"));
			}
		}

		else if (strcmp(elem->Value(), "scale") == 0) {
			t.setScale(elem->ToElement()->FloatAttribute("x"),
				elem->ToElement()->FloatAttribute("y"),
				elem->ToElement()->FloatAttribute("z"));
			}

		transformers.push_back(t);
		elem = elem->NextSiblingElement();
	}
	return transformers;
}



Group readXMLGroup(XMLNode* group) {
	Group g = Group();
	XMLNode* next = group->FirstChild();
	while (next) {
		if (strcmp(next->Value(), "transform") == 0) {
			g.addTransform(readXMLTransform(next));
		}
		else if (strcmp(next->Value(), "models") == 0) {
			XMLElement* elem = next->FirstChildElement("model");
			while (elem) {
				string s = std :: string(elem->Attribute("file"));
				g.addFile3d(s);
				lerFicheiro3d(s, &g);
				elem = elem->NextSiblingElement("model");
			}
		}
		else if (strcmp(next->Value(), "group") == 0) {
			g.addFilho(readXMLGroup(next));

		}
	next = next->NextSibling();
	}
	return g;
}



Group readXML(const char* file, Camera* camera) {
	XMLDocument doc;
	doc.LoadFile(file);
	
	XMLNode* world = doc.RootElement();
	XMLNode* next = world->FirstChild();
	Group g = Group();

	while (next) {
		if (strcmp(next->Value(), "camera") == 0) {
			readXMLCamera(next, camera);
		}
		else if (strcmp(next->Value(), "group") == 0) {
			g = readXMLGroup(next);			
		}
		else cout << "Ignora" << endl;
		next = next->NextSibling();
	}
	return g;
}


