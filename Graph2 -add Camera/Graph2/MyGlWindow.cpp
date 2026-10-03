#include "MyGlWindow.h"
//------------------------------View Matrix
static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };


ShaderProgram* ShaderObject;

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;
	m_cube = 0;

	//------------------------------View Matrix
	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);


	initialize();
}

void MyGlWindow::initialize() {
	m_cube = new ColorCube();
	m_model = Model();
	ShaderObject = new ShaderProgram();
	//load shaders
	ShaderObject->initFromFiles("Simple.vert", "Simple.frag"); //순서 주의 addUniform전에 얘 먼저 와야함
	//ShaderObject->addUniform("model");
	//ShaderObject->addUniform("view");
	//ShaderObject->addUniform("projection");
	ShaderObject->addUniform("mvp");
}


void MyGlWindow::draw()
{
	//백그라운드
	glClearColor(0.2f, 0.2f, 0.2f, 0);
	//컬러와 뎁스 버퍼 clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//어디에 그리나
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_DEPTH_TEST);  //enable depth testing

	//------------------------------View Matrix
	glm::vec3 eye = m_viewer->getViewPoint();
	glm::vec3 look = m_viewer->getViewCenter();
	glm::vec3 up = m_viewer->getUpVector();

	glm::mat4 view = lookAt(eye, look, up);

	glm::mat4 projection = glm::perspective(45.0f, 1.0f * m_width / m_height, 0.1f, 500.0f);
	glm::mat4 mview = view * m_model.getMatrix();
	glm::mat4 mvp = projection * view * m_model.getMatrix();


	//그려줌
	ShaderObject->use();  //vertex shader 호출

	//유니폼 처리
	/*glUniformMatrix4fv(ShaderObject->uniform("model"), 1, GL_FALSE, glm::value_ptr(m_model.getMatrix()));
	glUniformMatrix4fv(ShaderObject->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(ShaderObject->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));*/
	glUniformMatrix4fv(ShaderObject->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
	//세 개의 행렬을 하나로 결합해서 보냄

	if (m_cube) {
		m_cube->draw();
	}

	ShaderObject->disable();

}
