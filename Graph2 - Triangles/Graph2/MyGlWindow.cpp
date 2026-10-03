#include "MyGlWindow.h"

ShaderProgram* ShaderObject;
GLuint vaoHandle;  //vao handler
GLuint vboPosition;  //vbo handler(position)
GLuint vboColor; //vbo handler(color)
GLuint vbo;

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	setupBuffer();
}


void MyGlWindow::setupBuffer()
{
	ShaderObject = new ShaderProgram();

	//load shaders
	ShaderObject->initFromFiles("Simple.vert", "Simple.frag");

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
		1.0, 1.0, 1.0,
	};

	//VAO 생성
	GLushort cube_elements[] = {
		0, 1, 2,		2, 3, 0,		1, 5, 6,
		6, 2, 1,		7, 6, 5,		5, 4, 7,
		4, 0, 3,		3, 7, 4,		4, 5, 1,
		1, 0, 4,		3, 2, 6,		6, 7, 3,
	};


	glCreateVertexArrays(1, &vaoHandle);  //vao 생성
	glBindVertexArray(vaoHandle);  ///여기에 작업할거다 activate 의 의미..


	glGenBuffers(1, &vboPosition);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition); //여기 vbo를 이용함
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


	glGenBuffers(1, &vboColor);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vboColor); //여기 vbo를 이용함
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
	GLuint ibo_cube_elements;
	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glBindVertexArray(0);  //이 VAO를 close
}

void MyGlWindow::draw()
{
	//백그라운드
	glClearColor(0.2f, 0.2f, 0.2f, 0);
	//컬러와 뎁스 버퍼 clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//어디에 그리나
	glViewport(0, 0, m_width, m_height);


	//그려줌
	ShaderObject->use();  //vertex shader 호출

	glBindVertexArray(vaoHandle);

	int size;

	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	float tt = size / sizeof(GLushort);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	ShaderObject->disable();

}
