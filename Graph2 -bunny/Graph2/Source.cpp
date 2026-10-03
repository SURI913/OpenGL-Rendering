#include <iostream>
///순서 바뀌면 x
#include "glm/glm.hpp"
#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "MyGlWindow.h"

GLFWwindow* window;
MyGlWindow* myWindow;

bool lbutton_down;
bool rbutton_down;
bool mbutton_down;
double m_lastMouseX;
double m_lastMouseY;
double cx, cy;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	//esc누르면 종료
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	myWindow->setSize(width, height);
	myWindow->setAspect(width / (float)height);

}


static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	cx = xpos;
	cy = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		m_lastMouseX = xpos;
		m_lastMouseY = ypos;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_PRESS == action)
			lbutton_down = true;
		else if (GLFW_RELEASE == action)
			lbutton_down = false;
	}

	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (GLFW_PRESS == action)
			rbutton_down = true;
		else if (GLFW_RELEASE == action)
			rbutton_down = false;
	}

	else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		if (GLFW_PRESS == action)
			mbutton_down = true;
		else if (GLFW_RELEASE == action)
			mbutton_down = false;
	}
}

void mouseDragging(double width, double height)
{


	if (lbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		myWindow->m_viewer->rotate(fractionChangeX, fractionChangeY);
	}
	else if (mbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		myWindow->m_viewer->zoom(fractionChangeY);
	}
	else if (rbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		myWindow->m_viewer->translate(-fractionChangeX, -fractionChangeY, 1);
	}
	m_lastMouseX = cx;
	m_lastMouseY = cy;
}


int main() {
	/* Initialize the library */
	if (!glfwInit())
	{
		// Initialization failed
		return 0;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Suri FrameWork", NULL, NULL); //윈도우 만들어내는 함수. 첫번째 null 모니터, 두번째 Full Screen
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// glfw 먼저 초기화->gl3w 초기화 , 헤더파일은 반대임
	glfwMakeContextCurrent(window);
	if (gl3wInit()) {
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}
	if (!gl3wIsSupported(4, 6)) {
		fprintf(stderr, "OpenGL 4.6 not supported\n");
		return -1;
	}

	//frame rate 맞춰줌 1넣으면 자동으로 맞춰주고 0이면 안맞춰줌
	glfwSwapInterval(1);  //enable vsync

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback); //각 이벤트당 콜백 이벤트들 지정하는 함수. 지금은 키를 눌렀을때 마다 자동으로 호출되는 함수임
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);


	myWindow = new MyGlWindow(width, height);

	//가장 중요한 부분 윈도우가 열려있는 동안 뭔가 하는 부분?
	while (!glfwWindowShouldClose(window))
	{     ////////////////////////////

		myWindow->draw();

		//입력 읽는함수
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		//-------------마우스 움직임
		mouseDragging(width, height);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}