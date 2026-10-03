#pragma once
#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <vector>
class Cow {
public:
	Cow();
	std::vector<glm::vec3> normals;
	void draw();
private:
	GLuint vaoHandle;
	GLuint vbo_cow_vertices, vbo_cow_colors;
	GLuint ibo_cow_elements;
	void SetUp();
};
