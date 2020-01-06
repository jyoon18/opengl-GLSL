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

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
