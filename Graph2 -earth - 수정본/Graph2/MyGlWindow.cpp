#include "MyGlWindow.h"
//------------------------------View Matrix : cows
//static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
//static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
//static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

static float DEFAULT_VIEW_POINT[3] = { 150, 150, 150 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };



ShaderProgram* ShaderObject;
ShaderProgram* ShaderFloor;

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	//------------------------------View Matrix
	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);


	initialize();
}

void MyGlWindow::initialize() {
	m_object = new Bunny(10, 30,30);
	m_floor = new Floor(50,20);
	m_model = new Model();
	ShaderObject = new ShaderProgram();
	ShaderFloor = new ShaderProgram();
	//load shaders 
	ShaderObject->initFromFiles("texture.vert", "texture.frag"); //순서 주의 addUniform전에 얘 먼저 와야함
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
	ShaderObject->addUniform("Tex1"); //Projection * View * Model : mat4


	//load shaders 바닥
	ShaderFloor->initFromFiles("Floor.vert", "Simple.frag"); //순서 주의 addUniform전에 얘 먼저 와야함
	ShaderFloor->addUniform("LightLocation");  //Light Position : vec4
	ShaderFloor->addUniform("Kd");  //Diffuse Object Color :vec3
	ShaderFloor->addUniform("Ld");  //Diffuse Light Color : vec3
	ShaderFloor->addUniform("Ka");  //Diffuse Object Color :vec3
	ShaderFloor->addUniform("La");  //Diffuse Light Color : vec3
	ShaderFloor->addUniform("Ks");  //Diffuse Object Color :vec3
	ShaderFloor->addUniform("Ls");  //Diffuse Light Color : vec3
	ShaderFloor->addUniform("ModelViewMatrix");  //View*Model : mat4
	ShaderFloor->addUniform("NormalMatrix"); //Refer next slide : mat4
	ShaderFloor->addUniform("MVP"); //Projection * View * Model : mat4

	ShaderObject->addUniform("Tex1");
	ShaderObject->addUniform("GLuint tex_2d[2];
Tex2");

}

float rotationAngle = 0.0f;  // 초기 회전 각도
float rotationSpeed = 0.5f;  // 회전 속도



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
	float move = 10;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 floor_model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 15.0f, 0));
	// 카메라에서 지구까지의 거리
	float distanceFromCamera = 5.0f;

	// 지구를 y축을 중심으로 회전시키기
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationAngle += rotationSpeed;  // 회전 각도 증가



	glm::mat4 projection = glm::perspective(45.0f, 1.0f * m_width / m_height, 0.1f, 500.0f);
	glm::mat4 modelview = view * model;
	glm::mat4 floor_modelview = view * floor_model;
	glm::mat4 mvp = projection * modelview;
	glm::mat4 floor_mvp = projection * floor_modelview;

	//카메라 좌표계

	glm::mat4 inverseModelView = glm::inverse(modelview);
	glm::mat4 inverseFloorView = glm::inverse(floor_modelview);
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseModelView));
	glm::mat3 floor_normalMatrix = glm::mat3(glm::transpose(inverseFloorView));


	glm::vec4 lightPos(20, 50, 50, 1);  // 광원 위치

	glm::vec3 cow_Kd(1, 1, 1);   // 확산 개체 색상
	glm::vec3 cow_Ld(1, 1, 1);   // 확산 광원 색상

	glm::vec3 cow_Ka(0.3, 0.3, 0.3);   // 주변 개체 색상
	glm::vec3 cow_La(1, 1, 1);   // 주변 광원 색상

	glm::vec3 cow_Ks(0.3, 0.3, 0.3);   // 반사 개체 색상
	glm::vec3 cow_Ls(1, 1, 1);   // 반사 광원 색상

	glm::vec3 floor_Kd(0.7, 0.7, 0.7);   // 바닥의 확산 개체 색상 (회색)
	glm::vec3 floor_Ld(1, 1, 1);   // 바닥의 확산 광원 색상 (흰색)

	glm::vec3 floor_Ka(0.2, 0.2, 0.2);   // 바닥의 주변 개체 색상 (진한 회색)
	glm::vec3 floor_La(0.8, 0.8, 0.8);   // 바닥의 주변 광원 색상 (연한 회색)

	glm::vec3 floor_Ks(0.3, 0.3, 0.3);   // 바닥의 반사 개체 색상 (진한 회색)
	glm::vec3 floor_Ls(1, 1, 1);   // 바닥의 반사 광원 색상 (흰색)


	//그려줌
	ShaderObject->use();  //vertex shader 호출

	//유니폼 처리
	glUniform4fv(ShaderObject->uniform("LightLocation"),1, glm::value_ptr(lightPos));     //for LightPos
	glUniform3fv(ShaderObject->uniform("Kd"), 1, glm::value_ptr(cow_Kd));     //for Kd
	glUniform3fv(ShaderObject->uniform("Ld"), 1, glm::value_ptr(cow_Ld));     //for Ld

	glUniform3fv(ShaderObject->uniform("Ka"), 1, glm::value_ptr(cow_Ka));     //for Ka
	glUniform3fv(ShaderObject->uniform("La"), 1, glm::value_ptr(cow_La));     //for La

	glUniform3fv(ShaderObject->uniform("Ks"), 1, glm::value_ptr(cow_Ks));     //for Ks
	glUniform3fv(ShaderObject->uniform("Ls"), 1, glm::value_ptr(cow_Ls));     //for Ls

	glUniformMatrix4fv(ShaderObject->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(floor_modelview));  //modelView : 4x4 matrix
	glUniformMatrix3fv(ShaderObject->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));  //normalMatrix : 3x3 matrix

	glUniformMatrix4fv(ShaderObject->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

	//세 개의 행렬을 하나로 결합해서 보냄

	if (m_object) {
		m_object->draw();
	}
	ShaderObject->disable();

	///바닥
	ShaderFloor->use();

	//유니폼 처리
	glUniform4fv(ShaderFloor->uniform("LightLocation"), 1, glm::value_ptr(lightPos));     //for LightPos
	glUniform3fv(ShaderFloor->uniform("Kd"), 1, glm::value_ptr(floor_Kd));     //for Kd
	glUniform3fv(ShaderFloor->uniform("Ld"), 1, glm::value_ptr(floor_Ld));     //for Ld

	glUniform3fv(ShaderFloor->uniform("Ka"), 1, glm::value_ptr(floor_Ka));     //for Ka
	glUniform3fv(ShaderFloor->uniform("La"), 1, glm::value_ptr(floor_La));     //for La

	glUniform3fv(ShaderFloor->uniform("Ks"), 1, glm::value_ptr(floor_Ks));     //for Ks
	glUniform3fv(ShaderFloor->uniform("Ls"), 1, glm::value_ptr(floor_Ls));     //for Ls

	glUniformMatrix4fv(ShaderFloor->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(floor_modelview));  //modelView : 4x4 matrix
	glUniformMatrix3fv(ShaderFloor->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(floor_normalMatrix));  //normalMatrix : 3x3 matrix

	glUniformMatrix4fv(ShaderFloor->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(floor_mvp));
	//세 개의 행렬을 하나로 결합해서 보냄

	if (m_floor) {
		m_floor->draw();
	}
	ShaderFloor->disable();


}
