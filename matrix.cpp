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
#include "matrix.h"

void Matrix::boltMatrix() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(-30.0f, 45.0f, boltZpos + 105.0f));

	scalematrix = glm::scale(scalematrix, glm::vec3(0.15, 0.15, 0.4));
	tr = tx * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));


	if (bolt.keyVal == 1) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (bolt.keyVal == 2) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (bolt.keyVal == 3) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}
}

void Matrix::cameraMatrix() {
	glm::mat4 Projection = glm::ortho(-100.0, 100.0, -100.0, 100.0, -200.0, 200.0);
	MatrixID = glGetUniformLocation(programID, "projection");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Projection[0][0]);

	glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 2.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));   //eye, at, up
	MatrixID = glGetUniformLocation(programID, "viewTransform");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &View[0][0]);
}

void Matrix::launcherMatrix() {
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

	GLuint objColorID = glGetUniformLocation(programID, "objectColor");
	glUniform3f(objColorID, 1.0f, 1.0f, 0.9f);
}

void Matrix::mapMatrix() {
	tx = glm::mat4(1.0f);
	scalematrix = glm::mat4(1.0f);
	tr = glm::mat4(1.0f);

	tx = glm::translate(tx, glm::vec3(-30.0f, 0.0f, 0.0f));
	scalematrix = glm::scale(scalematrix, glm::vec3(0.7f, 0.7f, 0.7f));
	tr = tx * scalematrix;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(tr));

	GLuint objColorID = glGetUniformLocation(programID, "objectColor");
	glUniform3f(objColorID, 0.0f, 0.4f, 0.1f);
}

void Matrix::nutMatrixLeft() {
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
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (ranNum == 2) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (ranNum == 3) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}
}

void Matrix::nutMatrixRight() {
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
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.5, 0.1, 1.0);
	}
	else if (ranNum == 2) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 0.6, 1.0, 0.2);
	}
	else if (ranNum == 3) {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.2, 0);
	}
	else {
		GLuint objColorID = glGetUniformLocation(programID, "objectColor");
		glUniform3f(objColorID, 1.0, 0.7, 0.0);
	}
}
