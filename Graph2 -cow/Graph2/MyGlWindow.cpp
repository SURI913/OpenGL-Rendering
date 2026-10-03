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
	m_object = 0;

	//------------------------------View Matrix
	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);


	initialize();
}

void MyGlWindow::initialize() {
	m_object = new Cow();
	m_model = Model();
	ShaderObject = new ShaderProgram();
	//load shaders
	ShaderObject->initFromFiles("Simple.vert", "Simple.frag"); //순서 주의 addUniform전에 얘 먼저 와야함
	ShaderObject->addUniform("LightLocation");  //Light Position : vec4
	ShaderObject->addUniform("Kd");  //Diffuse Object Color :vec3
	ShaderObject->addUniform("Ld");  //Diffuse Light Color : vec3
	ShaderObject->addUniform("Ka");  //Diffuse Object Color :vec3
	ShaderObject->addUniform("La");  //Diffuse Light Color : vec3
	ShaderObject->addUniform("Ks");  //Diffuse Object Color :vec3
	ShaderObject->addUniform("Ls");  //Diffuse Light Color : vec3
	ShaderObject->addUniform("ModelViewMatrix");  //View*Model : mat4
	ShaderObject->addUniform("NormalMatrix"); //Refer next slide : mat4
	ShaderObject->addUniform("MVP"); //Projection * View * Model : mat4


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
	glm::mat4 modelview = view * m_model.getMatrix();
	glm::mat4 mvp = projection * modelview;

	//카메라 좌표계

	glm::mat4 inverseModelView = glm::inverse(modelview);
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseModelView));


	glm::vec4 lightPos(50, 50, 50, 1);  //light position
	glm::vec3 Kd(1, 1, 0);   //Diffuse Object Color
	glm::vec3 Ld(1, 1, 1);   //Diffuse Light Color

	glm::vec3 Ka(0.2, 0.2, 0);   //ambient Object Color
	glm::vec3 La(1, 1, 1);   //ambient Light Color

	glm::vec3 Ks(0.3, 0.3, 0);   //ambient Object Color
	glm::vec3 Ls(1, 1, 1);   //ambient Light Color

	//그려줌
	ShaderObject->use();  //vertex shader 호출

	//유니폼 처리
	glUniform4fv(ShaderObject->uniform("LightLocation"),1, glm::value_ptr(lightPos));     //for LightPos
	glUniform3fv(ShaderObject->uniform("Kd"), 1, glm::value_ptr(Kd));     //for Kd
	glUniform3fv(ShaderObject->uniform("Ld"), 1, glm::value_ptr(Ld));     //for Ld

	glUniform3fv(ShaderObject->uniform("Ka"), 1, glm::value_ptr(Ka));     //for Ka
	glUniform3fv(ShaderObject->uniform("La"), 1, glm::value_ptr(La));     //for La

	glUniform3fv(ShaderObject->uniform("Ks"), 1, glm::value_ptr(Ks));     //for Ks
	glUniform3fv(ShaderObject->uniform("Ls"), 1, glm::value_ptr(Ls));     //for Ls

	glUniformMatrix4fv(ShaderObject->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelview));  //modelView : 4x4 matrix
	glUniformMatrix3fv(ShaderObject->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));  //normalMatrix : 3x3 matrix

	glUniformMatrix4fv(ShaderObject->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
	//세 개의 행렬을 하나로 결합해서 보냄

	if (m_object) {
		m_object->draw();
	}

	ShaderObject->disable();

}
