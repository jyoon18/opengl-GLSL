#define _CRT_SECURE_NO_WARNINGS
#define winWidth 800
#define winHeight 800

#include <gl/glew.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm/common.hpp>
#include <Windows.h>
#include "loadOBJ.h"
#include "matrix.h"
#include "loadShader.h"
#include "declaration.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////

bool success{ false }, fire{ false }, gameOver{ false }, collision{ false };
int collisionTimeCheck{ 0 }, score{ 0 }, offTimeCheck{ 0 };
float mouseX, mouseY{ 0.0 };

std::vector< glm::vec3 > uvs;
std::vector< glm::vec3 > normals;

std::vector< glm::vec3 > mapVertices;
std::vector< glm::vec3 > launcherVertices;

std::vector <glm::vec3> bolt_01_vertices;
std::vector <glm::vec3> bolt_02_vertices;
std::vector <glm::vec3> bolt_03_vertices;
std::vector <glm::vec3> bolt_04_vertices;

GLuint ViewID, LightPosID, LightColorID;
GLuint vertexbuffer, normalbuffer;

Matrix *m = new Matrix;

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

bool map = loadOBJ("map_obj.obj", mapVertices, uvs, normals);
bool launcher = loadOBJ("launcher_obj.obj", launcherVertices, uvs, normals);
bool bolt01 = loadOBJ("bolt_01_obj.obj", bolt_01_vertices, uvs, normals);
bool bolt02 = loadOBJ("bolt_02_obj.obj", bolt_02_vertices, uvs, normals);
bool bolt03 = loadOBJ("bolt_03_obj.obj", bolt_03_vertices, uvs, normals);
bool bolt04 = loadOBJ("bolt_04_obj.obj", bolt_04_vertices, uvs, normals);


/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Term_project");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	m->programID = LoadShaders("testvs.txt", "testfs.txt");

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseMotion);

	glutDisplayFunc(display);
	glutMainLoop();
	delete m;
}

void display() {
	glClearColor(0.0f, 0.1f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(m->programID);

	ViewID = glGetUniformLocation(m->programID, "viewPos");
	glUniform3f(ViewID, -1, 1.5, 2);

	LightPosID = glGetUniformLocation(m->programID, "lightPos");
	glUniform3f(LightPosID, 0.0, 150.0, 0);

	LightColorID = glGetUniformLocation(m->programID, "lightColor");
	glUniform3f(LightColorID, 1.0, 1.0, 1.0);

	m->cameraMatrix();

	m->boltMatrix();
	draw(bolt_01_vertices);
	
	m->launcherMatrix();
	draw(launcherVertices);
	
	m->mapMatrix();
	draw(mapVertices);

	glutSwapBuffers();
	del();
}

void draw(std::vector< glm::vec3 > vertices) {
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
}

void del() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void mouseMotion(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (mouseX <0.55 && mouseX>-0.55 && mouseY <0.55 && mouseY>-0.55) {
			fire = true;
		}
	}

	mouseX = (float)(x - (float)800 / 2.0) * (float)(1.0 / (float)(800 / 2.0));
	mouseY = -(float)(y - (float)800 / 2.0) * (float)(1.0 / (float)(800 / 2.0));
}