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

using namespace std;

void display();
void draw(std::vector< glm::vec3 > vertices);
void del();
void keyboard(unsigned char key, int x, int y);
void mouseMotion(int button, int state, int x, int y);
void init();
void TimerFunction(int value);
void getRandom();
