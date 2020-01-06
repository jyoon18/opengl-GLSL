#include <gl/glew.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <time.h>
#include <glm/glm/common.hpp>
#include <Windows.h>

class Matrix {
	glm::mat4 tr = glm::mat4(1.0f);
	glm::mat4 tx = glm::mat4(1.0f);
	glm::mat4 rz = glm::mat4(1.0f);
	glm::mat4 scalematrix = glm::mat4(1.0f);

	float nutLeftXpos, nutRightXpos;
	int zrotDirLeft{ 0 }, zrotDirRight{ 0 };
	float nutZrotLeft, nutZrotRight = 0.0;
	float nutXpos{ 0.0 }, boltZpos{ 0.0 };
public:
	GLuint programID, MatrixID;
	int ranNum;

	struct kVal {
		int keyVal;
	};

	struct kVal nut;
	struct kVal bolt;

	void cameraMatrix();
	void mapMatrix();
	void launcherMatrix();
	void nutMatrixLeft();
	void nutMatrixRight();
	void boltMatrix();
};