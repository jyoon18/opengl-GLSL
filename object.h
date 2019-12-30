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

float nutLeftXpos, nutRightXpos;
int zrotDirLeft{ 0 }, zrotDirRight{ 0 };
bool success{ false }, fire{ false }, gameOver{ false }, collision{ false };
int collisionTimeCheck{ 0 }, score{ 0 }, offTimeCheck{ 0 };
float nutZrotLeft, nutZrotRight = 0.0;
float nutXpos{ 0.0 }, boltZpos{ 0.0 };

void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void display();
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
void cameraMatrix();

class MovingObject {
	GLuint vertexbuffer, normalbuffer;
	std::vector< glm::vec3 > normals;

public:
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

	MovingObject(std::vector< glm::vec3 > vertices);
	void nutMatrixLeft();
	void nutMatrixRight();
	void boltMatrix();
	void getRandom();
	~MovingObject();
};

class FixedObject {
public:
	void mapMatrix();
	void launcherMatrix();
};