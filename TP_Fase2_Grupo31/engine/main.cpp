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



Group g;

Camera camera = Camera();



void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glTranslatef(posx, 0.0, 0.0); //translate para traz e para a frente do eixo do x
	glTranslatef(0.0, posy, 0.0);


	glEnd();
}

void transforma(vector<Transform> transformers) {
	for (int i = 0; i < transformers.size(); i++) {
		Transform t = transformers.at(i);

		if (t.getFlagT()) {

			std::cout << t.getTranslate().getX() << endl;
			std::cout << t.getTranslate().getY() << endl;
			std::cout << t.getTranslate().getZ() << endl;

			glTranslatef(t.getTranslate().getX(), t.getTranslate().getY(), t.getTranslate().getZ()); //será que é o gl que não faz translate???

			std::cout << "MUITO NERVOSOOOOOOOOOO" << endl;
			std::cout << t.getTranslate().getX() << endl;
			std::cout << t.getTranslate().getY() << endl;
			std::cout << t.getTranslate().getZ() << endl;
		}
		else if(t.getFlagS()) {
			glScalef(t.getScale().getX(), t.getScale().getY(), t.getScale().getZ());
		}
		else if (t.getFlagR()) {
			glRotatef(t.getRotate().getAngle(), t.getRotate().getX(), t.getRotate().getY(), t.getRotate().getZ());
		}
	}
}


void desenha(Group gr) {

	
	
	glPushMatrix();

	transforma(gr.getTranforms());

	cout << "MERDA" << endl;
	vector<Vertex> vertices = gr.getVertexs();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	for(int i = 0; i < vertices.size(); i++) {
		glVertex3f(vertices.at(i).getVertexX(), vertices.at(i).getVertexY(), vertices.at(i).getVertexZ());
	}

	glEnd();
	for (int j = 0; j < gr.getFilhos().size(); j++) {
		desenha(gr.getFilho(j));
	}
	glPopMatrix();

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
	gluPerspective(fov,1,near,far);
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

	gluLookAt(px, py, pz,
		lx, ly, lz,
		ux, uy, uz);

	drawAxis();


	cout << "MERDAT" << endl;

	
	desenha(g);

	// End of frame
	glutSwapBuffers();
}



void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

}


int main(int argc, char** argv) {

	g = readXML("../testes/sistema_Solar.xml", &camera);

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
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
