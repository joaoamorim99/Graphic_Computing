#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <corecrt_math.h>
#include <iostream>
#include "parser.h"
#include "Vertex.h"


float posx = 0.0f;
float posy = 0.0f;


//float distancia = 5.0f;
//float angle = 0.0f;

vector<vector<Vertex>> vertices; //primeiro vetor são os ficheiros 3d
								 //segundo vetor sao os vertices de cada um desse ficheiro



Camera camera = Camera();
																				
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glTranslatef(posx, 0.0, 0.0); //translate para traz e para a frente do eixo do x
	glTranslatef(0.0, posy, 0.0);


	glEnd();
}




void desenha() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < vertices.size(); i++) { //iterar todas as figuras, ou seja, cada ficheiro 3d. 
		vector<Vertex> raquitico = vertices.at(i);
		//cout<< raquitico.size()<<endl;
		for (int j = 0; j < raquitico.size(); j++) { //iterar todos os pontos de um ficheiro 3d.
			glVertex3f(raquitico.at(j).getVertexX(), raquitico.at(j).getVertexY(), raquitico.at(j).getVertexZ());
		}
	}
	glEnd();
}






void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera

	float fov = camera.getProjection().getFov();
	float near = camera.getProjection().getNear();
	float far = camera.getProjection().getFar();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,
		1,
		near,
		far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float px = camera.getPosition().getX();
	float py = camera.getPosition().getY();
	float pz = camera.getPosition().getZ();
	float lx = camera.getLookAt().getX();
	float ly = camera.getLookAt().getY();
	float lz = camera.getLookAt().getZ();
	float ux = camera.getUp().getX();
	float uy = camera.getUp().getY();
	float uz = camera.getUp().getZ();

	gluLookAt(px, py ,pz,
		lx, ly, lz,
		ux, uy, uz);


	

	//drawAxis();

	/*
	geraPlane(2.0, 4);
	*/
	//geraCaixa(2, 2, 2, 8);
	desenha();
	// End of frame
	glutSwapBuffers();
}

// put code to process regular keys in here
	/*void moves(unsigned char key, int x, int y) {
		if ('w' == key) {
			distancia-=0.5;
		}
		if ('s' == key) {
			distancia+=0.5;

		}
		if ('a' == key) {
			angle-= 0.1;
		}
		if ('d' == key) {
			angle+= 0.1;
		}
		glutPostRedisplay();
	}
*/


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}

//C:/Users/admin/Desktop/CG/Guiao3/code(1)
int main(int argc, char** argv) {
	vector<string> file3d;
	file3d = readXML("../testes/test_1_3.xml",&camera);
	//std::cout << "aqui" << camera.getProjection().getFar() << "\n";
	//std::cout << camera.getLookAt().getX() << "\n";

	/*
	for (int i = 0; i < file3d.size(); i++) {
		std::cout << file3d.at(i) << "\n";
	}
	*/
	for (int i = 0; i < file3d.size(); i++) { //iterar ficheiros 3d transformar num vetor de pontos.
		vertices.push_back(lerFicheiro3d("../" + file3d.at(i)));
	}


	//std::cout << vertices.at(0).at(0).getVertexX();


	


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	//glutKeyboardFunc(moves);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glPolygonMode(GL_FRONT, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	

	
// enter GLUT's main cycle
	glutMainLoop();

	

	
	return 1;
}
