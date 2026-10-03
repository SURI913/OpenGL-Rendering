#include "ColorCube.h"

ColorCube::ColorCube() {
	setup();
}

void ColorCube::setup()  //Call from constructor
{
	//Create VAO for vertex position
	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};



	//Create VBO for vertex color
	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0
	};


	//Create a buffer for vertex index
	GLushort cube_elements[] = {
		0, 1, 2,		2, 3, 0,		1, 5, 6,
		6, 2, 1,		7, 6, 5,		5, 4, 7,
		4, 0, 3,		3, 7, 4,		4, 5, 1,
		1, 0, 4,		3, 2, 6,		6, 7, 3
	};

	//VAO 생성

	glCreateVertexArrays(1, &vaoHandle);  //vao 생성
	glBindVertexArray(vaoHandle);  ///여기에 작업할거다 activate 의 의미..


	glGenBuffers(1, &vbo_cube_vertices);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(0); // 0번 attr enable


	glGenBuffers(1, &vbo_cube_colors);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(1); // 1번 attr enable

	//이 사이에 들어감
	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glBindVertexArray(0);  //이 VAO를 close
}

void ColorCube::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

