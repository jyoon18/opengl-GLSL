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
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <glm/glm/common.hpp>

using namespace std;

glm::mat4 tr = glm::mat4(1.0f);
glm::mat4 tx = glm::mat4(1.0f);
glm::mat4 rz = glm::mat4(1.0f);
glm::mat4 scalematrix = glm::mat4(1.0f);

GLuint programID;
GLuint MatrixID;
GLuint LightPosID, LightColorID, objColorID, ViewID;

void display();
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
void cameraMatrix();

void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void mouseMotion(int, int, int, int);
void initNuts();
void initFont();
void BuildFont();
void killFont();
void backGroundMusic();

class MovingObject {
	GLuint vertexbuffer, normalbuffer;
	std::vector< glm::vec3 > normals;

	std::vector< glm::vec3 > nutVertices;
	std::vector< glm::vec3 > boltVertices;

	std::vector< glm::vec3 > nut_01_vertices;
	std::vector< glm::vec3 > nut_02_vertices;
	std::vector< glm::vec3 > nut_03_vertices;
	std::vector< glm::vec3 > nut_04_vertices;

	std::vector <glm::vec3> bolt_01_vertices;
	std::vector <glm::vec3> bolt_02_vertices;
	std::vector <glm::vec3> bolt_03_vertices;
	std::vector <glm::vec3> bolt_04_vertices;


	float nutZrotLeft, nutZrotRight = 0.0;
	float nutXpos{ 0.0 }, boltZpos{ 0.0 };
	float nutLeftXpos, nutRightXpos;
	int zrotDirLeft{ 0 }, zrotDirRight{ 0 };

public:
	MovingObject(std::vector< glm::vec3 > vertices);
	void nutMatrixLeft();
	void nutMatrixRight();
	void getRandom();
	void boltMatrix();
	~MovingObject();
};

class FixedObject {
	glm::mat4 tr = glm::mat4(1.0f);
	glm::mat4 tx = glm::mat4(1.0f);
	glm::mat4 rz = glm::mat4(1.0f);
	glm::mat4 scalematrix = glm::mat4(1.0f);

public:
	void mapMatrix();
	void launcherMatrix();
};