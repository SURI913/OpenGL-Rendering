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

	//-----Color
	float Color[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		1.0f, 1.0f,1.0f,
	};

	float Position[] = {
		-0.1f, -0.1f, 0.0f, 1.0f,
		0.1f, -0.1f, 0.0f, 1.0f,
		 0.1f,  0.1f, 0.0f, 1.0f,
		-0.1f,  0.1f, 0.0f, 1.0f,
	};

	//VAO 생성
	glCreateVertexArrays(1, &vaoHandle);  //vao 생성
	glBindVertexArray(vaoHandle);  ///여기에 작업할거다 activate 의 의미..


	glGenBuffers(1, &vboPosition);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(Position), Position, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,  //attr의 번호
		4,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(0); // 0번 attr enable


	glGenBuffers(1, &vboColor);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vboColor); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(1); // 1번 attr enable

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

	glBindVertexArray(vaoHandle);  //vao pickup
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  //triangle 프리미티브로 그림 (vertex 0부터 4까지)

	ShaderObject->disable();

}
