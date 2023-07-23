#include "parser.h"

string aux = "";


void lerFicheiro3d(string file3d, Group* g) {
	std::ifstream file;

	file.open("../testes/" + file3d);

	if (file.fail()) {
		std::cerr << "Erro a abrir o ficheiro\n";
		exit(1);
	}

	vector<Vertex> vertices, normais,texturas;


	Vertex v,nl,t;
	float x, y, z;

	int n, ni, ti, w, i  = 0;

	//vai buscar o número de vertices na 1ª linha do ficheiro, que é igual ao número de normais
	file >> n;
	//percorre o ficheiro e le as coordenadas de cada vertice e guarda no vetor
	while (i < n) {
		file >> x >> y >> z;
		v = Vertex(x, y, z);
		vertices.push_back(v);
		i++;
	} 
	//adiciona o vetor de vértices ao grupo
	g->addVertices(vertices);
	
	//vai buscar o número de indices
	file >> ni;
	//percorre o ficheiro e le os indices e guarda à lista de indíces do group
	for (i = 0; i < ni; i++) {
		file >> w;
		g->addIndices(w);
	}

	//percorre o ficheiro e le as coordenadas de cada vertice e guarda no vetor
	i = 0;
	while (i < n) {
		file >> x >> y >> z;
		nl = Vertex(x, y, z);
		normais.push_back(nl);
		i++;
	}
	//adiciona o vetor de vértices ao grupo
	g->addNormais(normais);

	//vai buscar o número de indices
	file >> ti;
	//percorre o ficheiro e le as coordenadas de textura e guarda no vetor
	for (i = 0; i < ti; i++) {
		file >> x >> y;
		t = Vertex(x, y, 0.0);
		texturas.push_back(t);
	}
	//adiciona o vetor de texturas ao grupo
	g->addTexturas(texturas);

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


void readXMLLight(XMLNode* lights, SysLight *light) {
	XMLNode* next = lights->FirstChild(); 

	while (next) {
		if(strcmp( next->ToElement()->Attribute("type"),"directional") == 0){
			light->addLight(next->ToElement()->Attribute("type"),
				next->ToElement()->FloatAttribute("dirx"),
				next->ToElement()->FloatAttribute("diry"),
				next->ToElement()->FloatAttribute("dirz"));
		}
		else if(strcmp(next->ToElement()->Attribute("type"), "point") == 0) {
			light->addLight(next->ToElement()->Attribute("type"),
				next->ToElement()->FloatAttribute("posx"),
				next->ToElement()->FloatAttribute("posy"),
				next->ToElement()->FloatAttribute("posz"));
		}
		else {
			light->addLight(next->ToElement()->Attribute("type"),
				next->ToElement()->FloatAttribute("posx"),
				next->ToElement()->FloatAttribute("posy"),
				next->ToElement()->FloatAttribute("posz"));
		}
		//std::cout << light->getLight().getVar() << endl;
		
		//cout << "LUZ" << endl;
		//for (int l = 0; l < light->getLights().size(); l++) {
			//std::cout << light->getLights().at(l).getVar() << endl; //.getVar() << endl;
			//std::cout << light->getLights().at(l).getDirX() << endl;
			//std::cout << light->getLights().at(l).getDirY() << endl;
			//std::cout << light->getLights().at(l).getDirZ() << endl;}


		next = next->NextSiblingElement();
	}
}



vector<Transform> readXMLTransform(XMLNode* next) {
	vector<Transform> transformers;
	XMLNode* elem = next->FirstChild();
	
	while (elem) {
		Transform t = Transform();
		if (strcmp(elem->Value(), "translate") == 0) {

			if (elem->ToElement()->FloatAttribute("time")) {

				aux = "time";

				Translate translate = Translate();
				translate.setTime(elem->ToElement()->FloatAttribute(aux.c_str()));
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
			else  {

				aux = "x";

				t.setTranslateVertex(elem->ToElement()->FloatAttribute("x"),
					elem->ToElement()->FloatAttribute("y"),
					elem->ToElement()->FloatAttribute("z"));
			}
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
	/*
	for (int k = 0; k < transformers.size(); k++) {
		if(transformers.at(k).getFlagT()) cout << transformers.at(k).getTranslate().getTime() << endl;
	}*/
	return transformers;
}

void readXMLColor(XMLNode* next, Group *g) {

	if (strcmp(next->Value(), "color") == 0) {
		XMLNode* elem2 = next->FirstChild();
		while (elem2) {
			if (strcmp(elem2->Value(), "diffuse") == 0) {
				g->setDiffu(elem2->ToElement()->FloatAttribute("R")/255,
					elem2->ToElement()->FloatAttribute("G") / 255,
					elem2->ToElement()->FloatAttribute("B") / 255);
			}
			else if (strcmp(elem2->Value(), "ambient") == 0) {
				g->setAmbi(elem2->ToElement()->FloatAttribute("R") / 255,
					elem2->ToElement()->FloatAttribute("G") / 255,
					elem2->ToElement()->FloatAttribute("B") / 255);
			}
			else if (strcmp(elem2->Value(), "specular") == 0) {
				g->setSpec(elem2->ToElement()->FloatAttribute("R") / 255,
					elem2->ToElement()->FloatAttribute("G") / 255,
					elem2->ToElement()->FloatAttribute("B") / 255);
			}
			else if (strcmp(elem2->Value(), "emissive") == 0) {

				g->setEmiss(elem2->ToElement()->FloatAttribute("R") / 255,
					elem2->ToElement()->FloatAttribute("G") / 255,
					elem2->ToElement()->FloatAttribute("B") / 255);

			}

			else if (strcmp(elem2->Value(), "shininess") == 0) {
				g->setShini(elem2->ToElement()->FloatAttribute("value"));
			}
			elem2 = elem2->NextSiblingElement();
		}
	}
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
			XMLElement* elem2 = next->FirstChildElement("model");

			while (elem) {
				string s = std::string(elem->Attribute("file"));
				g.addFile3d(s);
				lerFicheiro3d(s, &g);

				bool a = elem2->FirstChildElement("texture") != NULL;
				if (a) {
					elem2 = elem2->FirstChildElement("texture");
					if (strcmp(elem2->Value(), "texture") == 0) {
						string img = std::string(elem2->Attribute("file"));
						g.addImagem(img);
						//std::cout << img << endl;

					}
					elem2 = elem2->NextSiblingElement();
				}
				else {
					elem2 = elem2->FirstChildElement("color");
				
					if (strcmp(elem2->Value(), "color") == 0) {
						readXMLColor(elem2, &g);
						//cout << "ADICIONEI\n";
					}
				}
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


Group readXML(const char* file, Camera* camera, SysLight *light) {
	XMLDocument doc;
	doc.LoadFile(file);
	
	XMLNode* world = doc.RootElement();
	XMLNode* next = world->FirstChild();
	Group g = Group();


	while (next) {
		if (strcmp(next->Value(), "camera") == 0) {
			readXMLCamera(next, camera);
		}
		else if (strcmp(next->Value(), "lights") == 0) {
			readXMLLight(next, light);
		}

		else if (strcmp(next->Value(), "group") == 0) {
			g = readXMLGroup(next);			
		}
		else cout << "Ignora" << endl;
		next = next->NextSibling();
	}
	return g;
}


