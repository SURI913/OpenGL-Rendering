#pragma once
#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <vector>
#include "Loader.h"


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

class Bunny {
public:
	Bunny();
	std::vector<glm::vec3> position;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec2> uv;
	void draw();
private:
	GLuint vaoHandle;
	GLuint vbo_bunny_vertices, vbo_bunny_colors, vbo_bunny_Texcoord;
	GLuint ibo_bunny_elements;
	void SetUp();
};

class Floor {
public:
	Floor(int size, int tilesNum);
	void draw();
private:
	int size;
	int tilesNum;
	GLuint vaoHandle;
	GLuint vbo_floor_vertices, vbo_floor_colors, vbo_floor_normals;
	GLuint ibo_floor_elements;
	void Buffers();
};

class Earth
{
public:
	Earth(float rad, GLuint sl, GLuint st);

	void setup();
	void draw();
	int getVertexArrayHandle();

	GLuint VAO, VBO_position, VBO_normal, VBO_texcoord, IBO;

private:
	float radius;
	GLuint nVerts, elements;
	GLuint slices, stacks;

	void generateVerts(float*, float*, float*, GLuint*);


};