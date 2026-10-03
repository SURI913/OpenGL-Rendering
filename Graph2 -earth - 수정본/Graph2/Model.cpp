#include "Model.h"

Model::Model() {
	//glm::mat4 model = scale * translate * rotate….

	glm::mat4 floor_model = glm::mat4(1.0f);  // 초기화된 모델 매트릭스
	glm::mat4 obj_model = glm::mat4(1.0f);  // 초기화된 모델 매트릭스


	float scaleX, scaleY, scaleZ;
	float translationX, translationY = 20, translationZ;
	glm::mat4 scale = glm::mat4(
		scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY, 0.0f, 0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 translate = glm::mat4(
		1.0f, 0.0f, 0.0f, translationX,
		0.0f, 1.0f, 0.0f, translationY,
		0.0f, 0.0f, 1.0f, translationZ,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// 회전 각도를 라디안 단위로 변환
	float radians = glm::radians(30.0f);

	// 회전 행렬 구성
	glm::mat4 rotate(1.0f);
	rotate[1][1] = cosf(radians);
	rotate[1][2] = -sinf(radians);
	rotate[2][1] = sinf(radians);
	rotate[2][2] = cosf(radians);

	//obj_model *= translate * rotate * scale;
}

glm::mat4 Model::GetFloorMatrix() {
	return floor_model;
}

glm::mat4 Model::GetOBJMatrix() {
	return obj_model;
}