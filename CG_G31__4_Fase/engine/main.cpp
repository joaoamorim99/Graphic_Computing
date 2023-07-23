#include <stdlib.h>
#include <stdio.h>
#include <corecrt_math.h>
#include <iostream>
#include "parser.h"
#include "Vertex.h"
#include "Curvas.h"


#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

float posx = 0.0f;

int startX, startY, tracking = 0;
float camX, camY, camZ;
int alpha = 0, beta = 45, r = 50;
float posy = 0.0f;

int timebase;
float frames;

//float *vertexB,*normalB;
vector<float> vertexB, normalB, textB;

bool CatmullLine = false, axis = false, pinta = true;


//float distancia = 5.0f;
//float angle = 0.0f;

int nBuffer = 0;
int nBufferaux = 0;

GLuint *vertices2, verticeCount, *indexs;

GLuint *normaisBuff,  *texturasImgBuff,*texturasCoordBuff;

unsigned int indexesCount[1000];

Group g;

Camera camera = Camera();
SysLight light = SysLight();

vector<unsigned int> indices;



float prev_y[3] = { 0,-1,0 };

void loadTexture(std::string s, int n) {
	unsigned int t, tw, th;
	unsigned char* texData;

	cout << s << endl;

	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texturasImgBuff[n]);

	glBindTexture(GL_TEXTURE_2D, texturasImgBuff[n]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void renderCatmullRomCurve(int numpontos, float** p) {
	float gt;
	float pos[4];
	float deriv[4];

	glBegin(GL_LINE_LOOP);
	for (gt = 0; gt < 1; gt += 0.01) {
		getGlobalCatmullRomPoint(gt, numpontos, p, pos, deriv);
		glVertex3fv(pos);
		//glNormal3f(0.0, 0.0, 0.0);
	}

	glEnd();
}

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


/*
* Fun��o framerate, acede � variavel global frame e incrementa-a,
* permitindo atrav�s da "glutSetWindowTitle" visualisar os frames/segundo
* no nome da janela
*/
void framerate() {
	char title[50];
	frames++;
	float time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		float fps = frames * 1000.0 / (time - timebase);
		timebase = time;
		frames = 0;
		sprintf(title, "TP-CG@DI-UM | %lf FPS", fps);
		glutSetWindowTitle(title);
	}

}

void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	float red[] = { 1.0,0.0,0.0,1.0 };
	float green[] = { 0.0,1.0,0.0,1.0 };
	float blue[] = { 0.0,0.0,1.0,1.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glTranslatef(posx, 0.0, 0.0); //translate para traz e para a frente do eixo do x
	glTranslatef(0.0, posy, 0.0);


	glEnd();
}



void transforma(vector<Transform> transformers) {
	float deriv[4];
	float pos[4];
	static int k = 0;
	//cout << transformers.size() << endl;
	for (int i = 0; i < transformers.size(); i++) {
		Transform t = transformers.at(i);

		if (t.getFlagTN()) {
			glTranslatef(t.getTranslate().getX(), t.getTranslate().getY(), t.getTranslate().getZ());
		}

		else if (t.getFlagT()) {
				float timeCat = t.getTranslate().getTime() + (k* (1/t.getTranslate().getTime() * 0.0008));
				//cout << "Trans " << i << endl;
				//cout << timeCat << endl;
				float** p = t.getTranslate().toFloat();
				if(CatmullLine) renderCatmullRomCurve(t.getTranslate().getPoint().size(), p);
			
				getGlobalCatmullRomPoint(timeCat, t.getTranslate().getPoint().size(), p, pos, deriv);
			
				glTranslatef(pos[0], pos[1], pos[2]);

				float x[4];
				x[0] = deriv[0];
				x[1] = deriv[1];
				x[2] = deriv[2];
				normalize(x);
				float z[4];
				cross(x, prev_y, z);
				normalize(z);

				float y[4];
				cross(z, x, y);
				normalize(y);
				memcpy(prev_y, y, 3 * sizeof(float));

				float m[16];
				buildRotMatrix(x, y, z, m);
				glMultMatrixf(m);
				k++;

		}
		

		else if (t.getFlagS()) {
			glScalef(t.getScale().getX(), t.getScale().getY(), t.getScale().getZ());
		}

		else if (t.getFlagR()) {
			glRotatef(t.getRotate().getVar(), t.getRotate().getX(), t.getRotate().getY(), t.getRotate().getZ());
		}
	}
}

void desenha(Group gr) {

	glPushMatrix();

	transforma(gr.getTranforms());


	vector<Vertex> vertices = gr.getVertexs();
	vector<Vertex> normais = gr.getNormais();
	vector<Vertex> texturas;

	//vertexB = (float*)malloc(sizeof(float)*vertices.size());
	
	for (int i = 0; i < vertices.size(); i++) {
		vertexB.push_back(vertices.at(i).getVertexX());
		vertexB.push_back(vertices.at(i).getVertexY());
		vertexB.push_back(vertices.at(i).getVertexZ());
		
		//Adiciona as normais ao buffer
		normalB.push_back(normais.at(i).getVertexX());
		normalB.push_back(normais.at(i).getVertexY());
		normalB.push_back(normais.at(i).getVertexZ());

		//glVertex3f(vertices.at(i).getVertexX(), vertices.at(i).getVertexY(), vertices.at(i).getVertexZ());
	}
	

	glBindBuffer(GL_ARRAY_BUFFER, vertices2[nBuffer]);
	glBufferData(GL_ARRAY_BUFFER, vertexB.size() * sizeof(float), vertexB.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normaisBuff[nBuffer]);
	glBufferData(GL_ARRAY_BUFFER, normalB.size()*sizeof(float), normalB.data(), GL_STATIC_DRAW);
	
	indices = gr.getIndices();
	indexesCount[nBuffer] = indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexs[nBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	if (gr.getImagens().size() > 0) {
		texturas = gr.getTexturas();
		for (int j = 0; j < texturas.size(); j++) {
			textB.push_back(texturas.at(j).getVertexX());
			textB.push_back(texturas.at(j).getVertexY());
		}
		glBindBuffer(GL_ARRAY_BUFFER, texturasCoordBuff[nBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textB.size(), textB.data(), GL_STATIC_DRAW);
		loadTexture("../testes/" + gr.getImagem(0), nBuffer);
	}

	nBuffer++;

	vertexB.clear();
	normalB.clear();
	textB.clear();

	

	for (int j = 0; j < gr.getFilhos().size(); j++) {
		desenha(gr.getFilho(j));
	}
	glPopMatrix();


}

void renderFigs(Group gr) {


		glPushMatrix();
		
		if(gr.getImagens().size() == 0){
			float ambi[] = { gr.getAmbi().getVertexX(),gr.getAmbi().getVertexY(), gr.getAmbi().getVertexZ(), 1.0 };
			float diffu[] = { gr.getDiffu().getVertexX(),gr.getDiffu().getVertexY(), gr.getDiffu().getVertexZ(), 1.0 };
			float spec[] = { gr.getSpec().getVertexX(),gr.getSpec().getVertexY(), gr.getSpec().getVertexZ(), 1.0 };
			float emiss[] = { gr.getEmiss().getVertexX(),gr.getEmiss().getVertexY(), gr.getEmiss().getVertexZ(), 1.0 };

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffu);
			glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
			glMaterialfv(GL_FRONT, GL_EMISSION, emiss);
			glMaterialf(GL_FRONT, GL_SHININESS, gr.getShini());
			}
		transforma(gr.getTranforms());

		if (gr.getImagens().size() > 0) glBindTexture(GL_TEXTURE_2D, texturasImgBuff[nBufferaux]);

		glBindBuffer(GL_ARRAY_BUFFER, vertices2[nBufferaux]);

		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, normaisBuff[nBufferaux]);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexs[nBufferaux]);

		glBindBuffer(GL_ARRAY_BUFFER, texturasCoordBuff[nBufferaux]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);

		glDrawElements(GL_TRIANGLES, indexesCount[nBufferaux], GL_UNSIGNED_INT, NULL);

		nBufferaux++;

		if (gr.getImagens().size() > 0) glBindTexture(GL_TEXTURE_2D, 0);
		for (int j = 0; j < gr.getFilhos().size(); j++) {
			renderFigs(gr.getFilho(j));

		}

		glPopMatrix();

}



void renderScene(void) {

	// clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(pinta) glPolygonMode(GL_FRONT, GL_FILL);
	else  glPolygonMode(GL_FRONT, GL_LINE);
	/*
	glBindBuffer(GL_ARRAY_BUFFER, vertices2[nBuffer]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, verticeCount);*/

	// set the camera

	float fov = camera.getProjection().getFov();
	float near = camera.getProjection().getNear();
	float far = camera.getProjection().getFar();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, 1, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float lx = camera.getLookAt().getVertexX();
	float ly = camera.getLookAt().getVertexY();
	float lz = camera.getLookAt().getVertexZ();
	float ux = camera.getUp().getVertexX();
	float uy = camera.getUp().getVertexY();
	float uz = camera.getUp().getVertexZ();

	gluLookAt(camX, camY, camZ,
		lx, ly, lz,
		ux, uy, uz);

	if(axis) drawAxis();

	for(int p = 0; p < light.getLights().size(); p++){
		
		Light luz = light.getLights().at(p);
		float pos[4] = {luz.getDirX(),luz.getDirY(), luz.getDirZ(), luz.getVar() };
		
		GLenum tag = 0x4000;
		tag = tag + p;
		
		//cout << tag << endl;

		//glLightfv(tag, GL_POSITION, pos);

		glLightfv(tag, GL_POSITION, pos);
		//glLightfv(GL_LIGHT1, GL_POSITION, pos)
	}
	


	nBufferaux = 0;
	renderFigs(g);

	

	framerate();
	// End of frame
	glutSwapBuffers();
}


void processMouseButtons(int button, int state, int xx, int yy) {

	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);
}


int calculaNBuffer(Group gr) {
	int n = 1;
	for (int i = 0; i < gr.getFilhos().size(); i++) {
		n += calculaNBuffer(gr.getFilho(i));
	}
	return n;
}

void reactKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		CatmullLine = !CatmullLine;
		break;
	case 'z':
		axis = !axis;
		break;
	case 'f':
		pinta = !pinta;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	g = readXML("../testes/bola.xml", &camera, &light);

	int n = calculaNBuffer(g);



	
	vertices2 = (GLuint*)malloc(sizeof(GLuint) *n);
	indexs = (GLuint*)malloc(sizeof(GLuint) *n);

	normaisBuff = (GLuint*)malloc(sizeof(GLuint) * n); 
	texturasImgBuff = (GLuint*)malloc(sizeof(GLuint) * n); 
	texturasCoordBuff = (GLuint*)malloc(sizeof(GLuint) * n);

	camX = camera.getPosition().getVertexX();
	camY = camera.getPosition().getVertexY();
	camZ = camera.getPosition().getVertexZ();

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");
	


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);


	// Callback registration for keyboard processing
	glutKeyboardFunc(reactKey);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	// init GLEW
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };
	float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (int p = 0; p < light.getLights().size(); p++) {

		GLenum tag = 0x4000;
		tag = tag + p;
		glEnable(tag);

		
		// light colors
		glLightfv(tag, GL_AMBIENT, dark);
		glLightfv(tag, GL_DIFFUSE, white);
		glLightfv(tag, GL_SPECULAR, white);

	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	
	// controls global ambient light
	

	glGenBuffers(n,vertices2);
	glGenBuffers(n,indexs);
	glGenBuffers(n, normaisBuff);
	glGenBuffers(n, texturasCoordBuff);

	desenha(g);


	// enter GLUT's main cycle
	glutMainLoop();



	return 1;
}
