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
#include "draw.h"
#include "matrix.h"
#include "loadShader.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////

void display();

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

bool success{ false }, fire{ false }, gameOver{ false }, collision{ false };
int collisionTimeCheck{ 0 }, score{ 0 }, offTimeCheck{ 0 };

std::vector< glm::vec3 > uvs;
std::vector< glm::vec3 > normals;

std::vector< glm::vec3 > mapVertices;
std::vector< glm::vec3 > launcherVertices;

Matrix *m = new Matrix;

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

bool map = loadOBJ("map_obj.obj", mapVertices, uvs, normals);
bool launcher = loadOBJ("launcher_obj.obj", launcherVertices, uvs, normals);

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

	GLuint ViewID = glGetUniformLocation(m->programID, "viewPos");
	glUniform3f(ViewID, -1, 1.5, 2);

	GLuint LightPosID = glGetUniformLocation(m->programID, "lightPos");
	glUniform3f(LightPosID, 0.0, 150.0, 0);

	GLuint LightColorID = glGetUniformLocation(m->programID, "lightColor");
	glUniform3f(LightColorID, 1.0, 0.0, 0.0);

	m->cameraMatrix();

	m->mapMatrix();
	draw(mapVertices, normals);

	m->launcherMatrix();
	draw(launcherVertices, normals);


	glutSwapBuffers();
	del();
}