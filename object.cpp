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
#include "object.h"

using namespace std;

struct elements {
	int key = 0;
};

GLuint programID;
GLuint MatrixID;
GLuint LightPosID, LightColorID, objColorID, ViewID;

struct elements nuts;
struct elements bolts;
int ranNum = 0;
MovingObject *ran, *Key;

MovingObject::MovingObject(std::vector< glm::vec3 > vertices) {
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

MovingObject::~MovingObject() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
}

void MovingObject::boltMatrix() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(-30.0f, 45.0f, boltZpos + 105.0f));

	scalematrix = glm::scale(scalematrix, glm::vec3(0.15, 0.15, 0.4));
	tr = tx * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));


	if (bolts.key == 1) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (bolts.key == 2) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (bolts.key == 3) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}

}

void MovingObject::nutMatrixLeft() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	rz = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(-60.0 + nutXpos, 45.0f, 35.0f));
	rz = glm::rotate(rz, glm::radians(nutZrotLeft), glm::vec3(0.0, 0.0, 1.0));

	scalematrix = glm::scale(scalematrix, glm::vec3(0.2, 0.2, 0.2));
	tr = tx * rz * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));

	if (ranNum == 1) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (ranNum == 2) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (ranNum == 3) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}
}

void MovingObject::nutMatrixRight() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	rz = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(0.0 - nutXpos, 45.0f, 35.0f));
	rz = glm::rotate(rz, glm::radians(nutZrotRight), glm::vec3(0.0, 0.0, 1.0));
	scalematrix = glm::scale(scalematrix, glm::vec3(0.2, 0.2, 0.2));
	tr = tx * rz * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));

	if (ranNum == 1) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (ranNum == 2) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (ranNum == 3) {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}
}

void MovingObject::getRandom() {
	srand((unsigned int)time(NULL));
	ranNum = rand() % 4 + 1;
	cout << "random Number: " << ranNum << endl;
	if (ranNum == 1) {
		nuts.key = 1;
		nutVertices = nut_01_vertices;
	}
	else if (ranNum == 2) {
		nuts.key = 2;
		nutVertices = nut_02_vertices;
	}
	else if (ranNum == 3) {
		nuts.key = 3;
		nutVertices = nut_03_vertices;
	}
	else {
		nuts.key = 4;
		nutVertices = nut_04_vertices;
	}
}

void FixedObject::launcherMatrix() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	rz = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	rz = glm::rotate(rz, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rz = glm::rotate(rz, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tx = glm::translate(tx, glm::vec3(-20.0f, 10.0f, 150.0f));
	scalematrix = glm::scale(scalematrix, glm::vec3(0.7f, 0.7f, 0.7f));
	tr = tx * scalematrix * tx * rz;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));

	objColorID = glGetUniformLocation(programID, "objectColor");
	glUniform3f(objColorID, 1.0f, 1.0f, 0.9f);
}

void FixedObject::mapMatrix() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(-30.0f, 0.0f, 0.0f));
	scalematrix = glm::scale(scalematrix, glm::vec3(0.7f, 0.7f, 0.7f));
	tr = tx * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));

	objColorID = glGetUniformLocation(programID, "objectColor");
	glUniform3f(objColorID, 0.0f, 0.4f, 0.1f);
}

void TimerFunction(int value) {
	zrotDirLeft = -1;
	zrotDirRight = 1;
	nutZrotLeft += 30 * zrotDirLeft;
	nutZrotRight += 30 * zrotDirRight;

	nutXpos += 4.0;
	nutLeftXpos = -60.0 + nutXpos;
	nutRightXpos = 0.0 - nutXpos;

	if (fire) {
		boltZpos -= 80.0;
	}

	if (32 >= nutXpos && 24 <= nutXpos && boltZpos == -80 && collisionTimeCheck == 0)
	{
		collision = true;
		if (nuts.key != bolts.key) {
			score -= 10;
		}
		else {
			score += 50;
		}
		++collisionTimeCheck;
	}
	else if (36 <= nutLeftXpos && -96 >= nutRightXpos) {
		nutXpos = 0.0;
		boltZpos = 0.0;
		collisionTimeCheck = 0;
		fire = false;
		collision = false;
		ran->getRandom();

		score -= 10;
	}
	if (collisionTimeCheck <= 4 && collisionTimeCheck >= 1)
	{
		nutXpos = 30;
		boltZpos = -75.0;
		nutZrotLeft = 0;
		nutZrotRight = 0;

		++collisionTimeCheck;
	}
	if (collisionTimeCheck == 4)
	{
		nutXpos = -30.0;
		boltZpos = 0.0;
		collisionTimeCheck = 0;
		fire = false;
		collision = false;
		ran->getRandom();
	}

	if (score < -50) {
		gameOver = true;
		offTimeCheck++;
	}

	if (score > 1050) {
		success = true;
		offTimeCheck++;
	}

	glutPostRedisplay();
	glutTimerFunc(80, TimerFunction, 1);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		// 1,2,3,4번을 눌러서 볼트 부품을 바꿀 수 있도록
	case '1':
		Key->boltVertices = Key->bolt_01_vertices;
		bolts.key = 1;
		break;
	case '2':
		Key->boltVertices = Key->bolt_02_vertices;
		bolts.key = 2;
		break;
	case '3':
		Key->boltVertices = Key->bolt_03_vertices;
		bolts.key = 3;
		break;
	case '4':
		Key->boltVertices = Key->bolt_04_vertices;
		bolts.key = 4;
		break;
	case 'q':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void display() {
	glClearColor(0.0f, 0.1f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glutSwapBuffers();
}

void cameraMatrix() {
	glm::mat4 Projection = glm::ortho(-100.0, 100.0, -100.0, 100.0, -200.0, 200.0);
	MatrixID = glGetUniformLocation(programID, "projection");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Projection[0][0]);

	glm::mat4 View = glm::lookAt(glm::vec3(-1, 1.5, 2.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));   //eye, at, up
	MatrixID = glGetUniformLocation(programID, "viewTransform");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &View[0][0]);
}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	const char* vertexInfoLog, *fragmentInfoLog, *shaderProgramInfoLog;

	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vertexInfoLog = "error";
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, (GLchar*)&vertexInfoLog);
		printf("%s\n", vertexInfoLog);
	}

	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		fragmentInfoLog = "error";
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, (GLchar*)&fragmentInfoLog);
		printf("%s\n", fragmentInfoLog);
	}

	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		shaderProgramInfoLog = "error";
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, (GLchar*)&shaderProgramInfoLog);
		printf("%s\n", shaderProgramInfoLog);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}