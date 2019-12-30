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
#include <Windows.h>
#include "function.h"

using namespace std;


struct elements {
	int key = 0;
};

struct elements nuts;
struct elements bolts;
int ranNum = 0;

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

void display() {
	glClearColor(0.0f, 0.1f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glutSwapBuffers();

}